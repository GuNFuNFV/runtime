
#include "../headers/custom_hash.h"

const rte_hash_cmp_eq_t alt_cmp_jump_table[ALT_NUM_KEY_CMP_CASES] = {
        NULL,
        alt_rte_hash_k16_cmp_eq,
        alt_rte_hash_k32_cmp_eq,
        alt_rte_hash_k48_cmp_eq,
        alt_rte_hash_k64_cmp_eq,
        alt_rte_hash_k80_cmp_eq,
        alt_rte_hash_k96_cmp_eq,
        alt_rte_hash_k112_cmp_eq,
        alt_rte_hash_k128_cmp_eq,
        memcmp
};
struct rte_hash* initialize_test_hash_table(int num_entries){
    struct rte_hash_parameters hash_params = {
            .name = "test",
            .entries = num_entries * 2,
            .key_len = sizeof(struct five_tuple),
            .hash_func = rte_jhash,
            .hash_func_init_val = 0,
    };
    struct rte_hash *hash = rte_hash_create(&hash_params);
    hash->num_buckets = num_entries;
    if (hash == NULL) {
        printf("error: hash table creation failed\n");
        exit(1);
    }
    struct five_tuple key;
    key.src_ip = 0;
    for (int i = 0; i < num_entries; i++) {
        key.src_ip = key.src_ip + 1;
        int offset = rte_hash_add_key(hash, &key);
        if (offset == -EINVAL) {
            printf("error: %d\n", offset);
            exit(1);
        }
    }
    // test lookup
    key.src_ip = 0;
    for (int i = 0; i < num_entries; i++) {
        key.src_ip = key.src_ip + 1;
        int offset = rte_hash_lookup(hash, &key);
        if (offset == -ENOENT) {
            printf("error: %d\n", offset);
            exit(1);
        }
        else{
            printf("local_offset: %d\n", offset);
            fflush(stdout);
        }
    }
    return hash;
}
