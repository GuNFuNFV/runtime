#include "bess_nat.h"
#include "json_helper.h"

static inline int power2(int a) {
    if (a == 0)
        return 1;
    else
        return 2 * power2(a - 1);
}


ACTOR_CONTROL_STATE_INIT(bess_nat_init) {
    struct NATControlState *natControlState = (struct NATControlState *) rte_malloc(NULL,
                                                                                    sizeof(struct NATControlState), 0);
    GET_INTEGER(config, natControlState, packet);
    char hash_table_name[32];
    snprintf(hash_table_name, 32, "test_hash_%d", core_id);
    struct rte_hash_parameters rteHashParameters;
    rteHashParameters.name = hash_table_name;
    int entry_num = power2(20);
    rteHashParameters.entries = entry_num * 2;
    rteHashParameters.key_len = sizeof(struct five_tuple);
    rteHashParameters.hash_func = rte_jhash;
    rteHashParameters.hash_func_init_val = 0;
    rteHashParameters.extra_flag = 0;
    rteHashParameters.socket_id = 0;
    rteHashParameters.extra_flag = 0;
    // initialize hash table
    natControlState->nat_table = rte_hash_create(&rteHashParameters);
    natControlState->destination_ip_list = (uint32_t *) rte_malloc(NULL, sizeof(uint32_t) * entry_num * 2, 0);
    int *flow_id_array = (int *) rte_malloc(NULL, sizeof(int) * entry_num, 0);
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
        int ret = rte_hash_add_key(natControlState->nat_table, &temp_fiveTuple);
        natControlState->destination_ip_list[ret] = *flow_id;
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
        int ret = rte_hash_lookup(natControlState->nat_table, &temp_fiveTuple);
        if (ret < 0) {
            printf("flow_id %d is not inserted\n", flow_id);
            exit(-1);
        }
    }
    rte_free(flow_id_array);

    return natControlState;
}