
#ifndef NFLAMBDA_RUNTIME_INTERLEAVED_HASH_H
#define NFLAMBDA_RUNTIME_INTERLEAVED_HASH_H
#include "key.h"
#include "common.h"
#include "debug.h"
#define EMPTY_SLOT			0

/* Structure that stores key-value pair */
struct rte_hash_key {
    union {
        uintptr_t idata;
        void *pdata;
    };
    /* Variable key size */
    char key[0];
};

/* All different signature compare functions */
enum rte_hash_sig_compare_function {
    RTE_HASH_COMPARE_SCALAR = 0,
    RTE_HASH_COMPARE_SSE,
    RTE_HASH_COMPARE_NEON,
    RTE_HASH_COMPARE_NUM
};

enum cmp_jump_table_case {
    KEY_CUSTOM = 0,
    KEY_16_BYTES,
    KEY_32_BYTES,
    KEY_48_BYTES,
    KEY_64_BYTES,
    KEY_80_BYTES,
    KEY_96_BYTES,
    KEY_112_BYTES,
    KEY_128_BYTES,
    KEY_OTHER_BYTES,
    NUM_KEY_CMP_CASES,
};
#define RTE_HASH_BUCKET_ENTRIES		8
/** Bucket structure */
struct rte_hash_bucket {
    uint16_t sig_current[RTE_HASH_BUCKET_ENTRIES];

    uint32_t key_idx[RTE_HASH_BUCKET_ENTRIES];

    uint8_t flag[RTE_HASH_BUCKET_ENTRIES];

    void *next;
} __rte_cache_aligned;

/** A hash table structure. */
struct rte_hash {
    char name[RTE_HASH_NAMESIZE];   /**< Name of the hash. */
    uint32_t entries;               /**< Total table entries. */
    uint32_t num_buckets;           /**< Number of buckets in table. */

    struct rte_ring *free_slots;
    /**< Ring that stores all indexes of the free slots in the key table */

    struct lcore_cache *local_free_slots;
    /**< Local cache per lcore, storing some indexes of the free slots */

    /* RCU config */
    struct rte_hash_rcu_config *hash_rcu_cfg;
    /**< HASH RCU QSBR configuration structure */
    struct rte_rcu_qsbr_dq *dq;	/**< RCU QSBR defer queue. */

    /* Fields used in lookup */

    uint32_t key_len __rte_cache_aligned;
    /**< Length of hash key. */
    uint8_t hw_trans_mem_support;
    /**< If hardware transactional memory is used. */
    uint8_t use_local_cache;
    /**< If multi-writer support is enabled, use local cache
     * to allocate key-store slots.
     */
    uint8_t readwrite_concur_support;
    /**< If read-write concurrency support is enabled */
    uint8_t ext_table_support;     /**< Enable extendable bucket table */
    uint8_t no_free_on_del;
    /**< If key index should be freed on calling rte_hash_del_xxx APIs.
     * If this is set, rte_hash_free_key_with_position must be called to
     * free the key index associated with the deleted entry.
     * This flag is enabled by default.
     */
    uint8_t readwrite_concur_lf_support;
    /**< If read-write concurrency lock free support is enabled */
    uint8_t writer_takes_lock;
    /**< Indicates if the writer threads need to take lock */
    rte_hash_function hash_func;    /**< Function used to calculate hash. */
    uint32_t hash_func_init_val;    /**< Init value used by hash_func. */
    rte_hash_cmp_eq_t rte_hash_custom_cmp_eq;
    /**< Custom function used to compare keys. */
    enum cmp_jump_table_case cmp_jump_table_idx;
    /**< Indicates which compare function to use. */
    enum rte_hash_sig_compare_function sig_cmp_fn;
    /**< Indicates which signature compare function to use. */
    uint32_t bucket_bitmask;
    /**< Bitmask for getting bucket index from hash signature. */
    uint32_t key_entry_size;         /**< Size of each key entry. */

    void *key_store;                /**< Table storing all keys and data */
    struct rte_hash_bucket *buckets;
    /**< Table with buckets storing all the	hash values and key indexes
     * to the key table.
     */
    rte_rwlock_t *readwrite_lock; /**< Read-write lock thread-safety. */
    struct rte_hash_bucket *buckets_ext; /**< Extra buckets array */
    struct rte_ring *free_ext_bkts; /**< Ring of indexes of free buckets */
    /* Stores index of an empty ext bkt to be recycled on calling
     * rte_hash_del_xxx APIs. When lock free read-write concurrency is
     * enabled, an empty ext bkt cannot be put into free list immediately
     * (as readers might be using it still). Hence freeing of the ext bkt
     * is piggy-backed to freeing of the key index.
     */
    uint32_t *ext_bkt_to_free;
    uint32_t *tbl_chng_cnt;
    /**< Indicates if the hash table changed from last read. */
} __rte_cache_aligned;

enum alt_cmp_jump_table_case {
    ALT_KEY_CUSTOM = 0,
    ALT_KEY_16_BYTES,
    ALT_KEY_32_BYTES,
    ALT_KEY_48_BYTES,
    ALT_KEY_64_BYTES,
    ALT_KEY_80_BYTES,
    ALT_KEY_96_BYTES,
    ALT_KEY_112_BYTES,
    ALT_KEY_128_BYTES,
    ALT_KEY_OTHER_BYTES,
    ALT_NUM_KEY_CMP_CASES,
};

const rte_hash_cmp_eq_t alt_cmp_jump_table[ALT_NUM_KEY_CMP_CASES];

static inline uint16_t
get_short_sig(const hash_sig_t hash) {
    return hash >> 16;
}

static inline uint32_t
get_prim_bucket_index(const struct rte_hash *h, const hash_sig_t hash) {
    return hash & h->bucket_bitmask;
}

static inline uint32_t
get_alt_bucket_index(const struct rte_hash *h,
                     uint32_t cur_bkt_idx, uint16_t sig) {
    return (cur_bkt_idx ^ sig) & h->bucket_bitmask;
}

static inline int
rte_hash_cmp_eq(const void *key1, const void *key2, const struct rte_hash *h) {

    return alt_cmp_jump_table[h->cmp_jump_table_idx](key1, key2, h->key_len);
}


static inline int32_t
search_one_bucket_l(const struct rte_hash *h, const void *key,
                    uint16_t sig, void **data,
                    const struct rte_hash_bucket *bkt) {
    int i;
    struct rte_hash_key *k, *keys = h->key_store;

    for (i = 0; i < RTE_HASH_BUCKET_ENTRIES; i++) {
        if (bkt->sig_current[i] == sig &&
            bkt->key_idx[i] != EMPTY_SLOT) {
            // this one should be prefetched
            k = (struct rte_hash_key *) ((char *) keys +
                                         bkt->key_idx[i] * h->key_entry_size);

            if (rte_hash_cmp_eq(key, k->key, h) == 0) {
                if (data != NULL)
                    *data = k->pdata;
                /*
                 * Return index where key is stored,
                 * subtracting the first dummy index
                 */
                return bkt->key_idx[i] - 1;
            }
        }
    }
    return -1;
}

#define FOR_EACH_BUCKET(CURRENT_BKT, START_BUCKET)                            \
    for (CURRENT_BKT = START_BUCKET;                                      \
        CURRENT_BKT != NULL;                                          \
        CURRENT_BKT = CURRENT_BKT->next)


static int
alt_rte_hash_k16_cmp_eq(const void *key1, const void *key2, size_t key_len __rte_unused) {
    const __m128i k1 = _mm_loadu_si128((const __m128i *) key1);
    const __m128i k2 = _mm_loadu_si128((const __m128i *) key2);
    const __m128i x = _mm_xor_si128(k1, k2);

    return !_mm_test_all_zeros(x, x);
}

static int
alt_rte_hash_k32_cmp_eq(const void *key1, const void *key2, size_t key_len) {
    return alt_rte_hash_k16_cmp_eq(key1, key2, key_len) ||
           alt_rte_hash_k16_cmp_eq((const char *) key1 + 16,
                                   (const char *) key2 + 16, key_len);
}

static int
alt_rte_hash_k48_cmp_eq(const void *key1, const void *key2, size_t key_len) {
    return alt_rte_hash_k16_cmp_eq(key1, key2, key_len) ||
           alt_rte_hash_k16_cmp_eq((const char *) key1 + 16,
                                   (const char *) key2 + 16, key_len) ||
           alt_rte_hash_k16_cmp_eq((const char *) key1 + 32,
                                   (const char *) key2 + 32, key_len);
}

static int
alt_rte_hash_k64_cmp_eq(const void *key1, const void *key2, size_t key_len) {
    return alt_rte_hash_k32_cmp_eq(key1, key2, key_len) ||
           alt_rte_hash_k32_cmp_eq((const char *) key1 + 32,
                                   (const char *) key2 + 32, key_len);
}

static int
alt_rte_hash_k80_cmp_eq(const void *key1, const void *key2, size_t key_len) {
    return alt_rte_hash_k64_cmp_eq(key1, key2, key_len) ||
           alt_rte_hash_k64_cmp_eq((const char *) key1 + 64,
                                   (const char *) key2 + 64, key_len);
}

static int
alt_rte_hash_k96_cmp_eq(const void *key1, const void *key2, size_t key_len) {
    return alt_rte_hash_k64_cmp_eq(key1, key2, key_len) ||
           alt_rte_hash_k32_cmp_eq((const char *) key1 + 64,
                                   (const char *) key2 + 64, key_len);
}

static int
alt_rte_hash_k112_cmp_eq(const void *key1, const void *key2, size_t key_len) {
    return alt_rte_hash_k64_cmp_eq(key1, key2, key_len) ||
           alt_rte_hash_k32_cmp_eq((const char *) key1 + 64,
                                   (const char *) key2 + 64, key_len) ||
           alt_rte_hash_k16_cmp_eq((const char *) key1 + 96,
                                   (const char *) key2 + 96, key_len);
}

static int
alt_rte_hash_k128_cmp_eq(const void *key1, const void *key2, size_t key_len) {
    return alt_rte_hash_k64_cmp_eq(key1, key2, key_len) ||
           alt_rte_hash_k64_cmp_eq((const char *) key1 + 64,
                                   (const char *) key2 + 64, key_len);
}



static inline void increment_value(void *value, int value_length) {
    // increment the last bit
    // carry over if necessary
    for (int i = value_length - 1; i >= 0; i--) {
        uint8_t *byte = (uint8_t *) value + i;
        if (*byte == 255) {
            *byte = 0;
        } else {
            *byte = *byte + 1;
            break;
        }
    }
}



static inline int32_t rtc_search(struct rte_hash *hash, void *key) {
    DEBUG_PRINT("hash pointer %p\n", hash);
    int ret;
    // get the hash of the key
    uint32_t hash_value = rte_jhash(key, sizeof(struct five_tuple), 0);
    DEBUG_PRINT("hash_value: %u\n", hash_value);
    DEBUG_PRINT("size of key: %lu\n", sizeof(struct five_tuple));

    hash_sig_t sig = hash_value;
    uint32_t prim_bucket_idx, sec_bucket_idx;
    struct rte_hash_bucket *bkt, *cur_bkt;
    int pos;
    uint16_t short_sig;
    // get the index of the bucket

    // check __rte_hash_lookup_with_hash_l
    short_sig = get_short_sig(sig);
    prim_bucket_idx = get_prim_bucket_index(hash, sig);
    struct rte_hash_bucket *prim_bkt;
    bkt = &hash->buckets[prim_bucket_idx];
    DEBUG_PRINT("prim_bucket_idx: %u\n", prim_bucket_idx);
    ret = search_one_bucket_l(hash, key, short_sig, NULL, bkt);
    if (ret != -1) {
//        DEBUG_PRINT("found\n");
//        DEBUG_PRINT("ret: %d\n", ret);
        return ret;
    }
    /* Calculate secondary hash */
    sec_bucket_idx = get_alt_bucket_index(hash, prim_bucket_idx, short_sig);
    bkt = &hash->buckets[sec_bucket_idx];

    /* Check if key is in secondary location */
    FOR_EACH_BUCKET(cur_bkt, bkt) {
        ret = search_one_bucket_l(hash, key, short_sig,
                                  NULL, cur_bkt);
        if (ret != -1) {
            return ret;
        }
        DEBUG_PRINT("not found in the bucket, go to next bucket\n");
    }
    return ret;
}

struct rte_hash* initialize_test_hash_table(int num_entries);
void* interleaved_lookup(struct rte_hash*hash);
//void initialize_benchmark(struct worker_fsm_context *context);

//enum STAGE {
//    HASH,
//    FIRST_LOOKUP,
//    SECOND_LOOKUP,
//    DONE,
//    PREFETCHING_INTERVAL,
//    SEARCHING,
//    SEARCHED
//};



#endif //NFLAMBDA_RUNTIME_INTERLEAVED_HASH_H
