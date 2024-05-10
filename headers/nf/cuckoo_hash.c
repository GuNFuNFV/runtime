#include "cuckoo_hash.h"

#include "tiny_json.h"



ACTOR_CONTROL_STATE_INIT(cuckoo_hash_init) {
    DEBUG_PRINT("cuckoo_hash_init\n");
    DEBUG_PRINT("%s\n", config);
    struct cuckoo_state *cuckooState = (struct cuckoo_state *) rte_malloc(NULL, sizeof(struct cuckoo_state), 0);
    cuckooState->cuckoo_hash_key_offset = (CONTROL_VARIABLE_OFFSET) 0;
    cuckooState->prim_bucket_idx_offset = (CONTROL_VARIABLE_OFFSET) sizeof(struct five_tuple);
    cuckooState->alt_bucket_idx_offset = (CONTROL_VARIABLE_OFFSET) sizeof(struct five_tuple) + sizeof(uint32_t);
    cuckooState->short_sig_offset = (CONTROL_VARIABLE_OFFSET) sizeof(struct five_tuple) + sizeof(uint32_t) * 2;
    cuckooState->core_id = core_id;

    _jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    // check whether contain cuckoo_hash_entry_num
    json_t const *cuckoo_hash_entry_num = json_getProperty(json, "cuckoo_hash_entry_num");
    json_t const *cuckoo_hash_key_size = json_getProperty(json, "cuckoo_hash_key_size");
    json_t const *cuckoo_hash_header_type = json_getProperty(json, "cuckoo_hash_header_type");
    json_t const *cuckoo_hash_get_key_done = json_getProperty(json, "cuckoo_hash_get_key_done");
    json_t const *cuckoo_hash_first_hash_done = json_getProperty(json, "cuckoo_hash_first_hash_done");
    json_t const *cuckoo_hash_first_test_failure = json_getProperty(json, "cuckoo_hash_first_test_failure");
    json_t const *cuckoo_hash_second_hash_done = json_getProperty(json, "cuckoo_hash_second_hash_done");
    json_t const *cuckoo_hash_test_success = json_getProperty(json, "cuckoo_hash_test_success");

    if (cuckoo_hash_entry_num)
        cuckooState->cuckoo_hash_entry_num = json_getInteger(cuckoo_hash_entry_num);
    if (cuckoo_hash_key_size)
        cuckooState->cuckoo_hash_key_size = json_getInteger(cuckoo_hash_key_size);
    if (cuckoo_hash_header_type)
        cuckooState->cuckoo_hash_header_type = (uint8_t) json_getInteger(cuckoo_hash_header_type);
    if (cuckoo_hash_get_key_done)
        cuckooState->cuckoo_hash_get_key_done = (EVENT) json_getInteger(cuckoo_hash_get_key_done);
    if (cuckoo_hash_first_hash_done)
        cuckooState->cuckoo_hash_first_hash_done = (EVENT) json_getInteger(cuckoo_hash_first_hash_done);
    if (cuckoo_hash_first_test_failure)
        cuckooState->cuckoo_hash_first_test_failure = (EVENT) json_getInteger(cuckoo_hash_first_test_failure);
    if (cuckoo_hash_second_hash_done)
        cuckooState->cuckoo_hash_second_hash_done = (EVENT) json_getInteger(cuckoo_hash_second_hash_done);
    if (cuckoo_hash_test_success)
        cuckooState->cuckoo_hash_test_success = (EVENT) json_getInteger(cuckoo_hash_test_success);
    return cuckooState;
}

int power2(int a) {
    if (a == 0)
        return 1;
    else
        return 2 * power2(a - 1);
}

AMAC_CLASSIFIER_INIT(cuckoo_hash_classifier) {
    struct cuckoo_state *cuckooState = control_state;
    char hash_table_name[32];
    snprintf(hash_table_name, 32, "test_hash_%d_%d", core_id, datablock_id);
    struct rte_hash_parameters rteHashParameters;
    rteHashParameters.name = hash_table_name;
    int entry_num = power2(cuckooState->cuckoo_hash_entry_num);
    rteHashParameters.entries = entry_num * 2;
    rteHashParameters.key_len = sizeof(struct five_tuple);
    rteHashParameters.hash_func = rte_jhash;
    rteHashParameters.hash_func_init_val = 0;
    rteHashParameters.extra_flag = 0;
    rteHashParameters.socket_id = 0;
    rteHashParameters.extra_flag = 0;
    struct rte_hash *temp_hash = rte_hash_create(&rteHashParameters);
    if (temp_hash == NULL) {
        exit(1);
    }
    int *flow_id_array;
    switch (cuckooState->cuckoo_hash_header_type) {
        case FIVE_TUPLE:
            flow_id_array = (int *) rte_malloc(NULL, sizeof(int) * entry_num, 0);
            for (int i = 0; i < entry_num; i++) {
                flow_id_array[i] = i;
            }
            // permute the flow_id_array
            // randomly shuffle the flow_id_array
            int pass = 10;
            for (int i = 0; i < pass; i++) {
                for (int i = 0; i < entry_num; i++) {
                    int j = rte_rand_max(entry_num);
                    int temp = flow_id_array[i];
                    flow_id_array[i] = flow_id_array[j];
                    flow_id_array[j] = temp;
                }
            }
            for (int i = 0; i < entry_num; i++) {
                int *flow_id = flow_id_array + i;
                struct five_tuple temp_fiveTuple;
                temp_fiveTuple.src_ip = rte_cpu_to_be_32(*flow_id);
                temp_fiveTuple.dst_ip = rte_cpu_to_be_32(core_id);
                temp_fiveTuple.src_port = 0;
                temp_fiveTuple.dst_port = 0;
//                temp_fiveTuple.proto = IPPROTO_TCP;
                int ret = rte_hash_add_key(temp_hash, &temp_fiveTuple);
//                assert(ret >= 0);
            }
            // check that whether the insertion is correct
            for (int i = 0; i < entry_num; i++) {
                int flow_id = i;
                struct five_tuple temp_fiveTuple;
                temp_fiveTuple.src_ip = rte_cpu_to_be_32(flow_id);
                temp_fiveTuple.dst_ip = rte_cpu_to_be_32(core_id);
                temp_fiveTuple.src_port = 0;
                temp_fiveTuple.dst_port = 0;
//                temp_fiveTuple.proto = IPPROTO_TCP;
                int ret = rte_hash_lookup(temp_hash, &temp_fiveTuple);
                if (ret < 0) {
                    printf("flow_id %d is not inserted\n", flow_id);
                    exit(-1);
                }
            }
            rte_free(flow_id_array);
            break;
        case SRC_IP:
            exit(-1);// not implemented yet
    }
    DEBUG_PRINT("cuckoo hash init done\n");
    struct five_tuple temp_fiveTuple;
    temp_fiveTuple.src_ip = rte_cpu_to_be_32(1);
    temp_fiveTuple.dst_ip = rte_cpu_to_be_32(core_id);
    temp_fiveTuple.src_port = 0;
    temp_fiveTuple.dst_port = 0;
//                temp_fiveTuple.proto = IPPROTO_TCP;
    int ret = rtc_search(temp_hash, &temp_fiveTuple);
    if (ret < 0) {
        printf("flow_id %d is not inserted\n", 1);
        exit(-1);
    }

    return temp_hash;
}


