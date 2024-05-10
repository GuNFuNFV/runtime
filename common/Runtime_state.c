#include "Runtime_state.h"
#include <libltdl/lt_system.h>
#include <sys/time.h>
#include <dirent.h>


struct config;
extern struct Runtime_state *c;

void install_flow() {
    struct rte_flow_error error;
    struct rte_flow_attr attr;
    struct rte_flow_item pattern[4];
    struct rte_flow_action action[2];
    struct rte_flow *flow;
    struct rte_flow_action_queue queue;
    struct rte_flow_item_ipv4 ip_spec;
    struct rte_flow_item_ipv4 ip_mask;
    struct rte_flow_item_tcp tcp_spec;
    struct rte_flow_item_tcp tcp_mask;
    uint32_t src_ip;
    uint32_t dst_ip;
    for (int i = 0; i < 24; i++) {
        uint16_t queue_id = i;
        queue.index = queue_id;

        printf("install flow rule\n");

        src_ip = (((0) << 24) + (0 << 16) + (0 << 8) + 0); /* src ip = 0.0.0.0 */
        dst_ip = ((0 << 24) + (0 << 16) + (0 << 8) + 0);
        int res;

        flow = NULL;
        memset(pattern, 0, sizeof(pattern));
        memset(action, 0, sizeof(action));

        memset(&attr, 0, sizeof(struct rte_flow_attr));
        attr.ingress = 1;

        action[0].type = RTE_FLOW_ACTION_TYPE_QUEUE;
        action[0].conf = &queue;
        action[1].type = RTE_FLOW_ACTION_TYPE_END;

        pattern[0].type = RTE_FLOW_ITEM_TYPE_ETH;

        //        memset(&ip_spec, 0, sizeof(struct rte_flow_item_ipv4));
        //        memset(&ip_mask, 0, sizeof(struct rte_flow_item_ipv4));
        //        ip_spec.hdr.dst_addr = htonl(dst_ip);
        //        ip_mask.hdr.dst_addr = EMPTY_MASK;
        //        ip_spec.hdr.src_addr = htonl(src_ip);
        //        ip_mask.hdr.src_addr = EMPTY_MASK;

        pattern[1].type = RTE_FLOW_ITEM_TYPE_IPV4;
        //        pattern[1].spec = &ip_spec;
        //        pattern[1].mask = &ip_mask;

        memset(&tcp_spec, 0, sizeof(struct rte_flow_item_tcp));
        memset(&tcp_mask, 0, sizeof(struct rte_flow_item_tcp));
        tcp_spec.hdr.dst_port = RTE_BE16(i);
        tcp_mask.hdr.dst_port = 0xffff;
        tcp_spec.hdr.src_port = RTE_BE16(0);
        tcp_mask.hdr.src_port = 0x0;

        pattern[2].type = RTE_FLOW_ITEM_TYPE_TCP;
        pattern[2].spec = &tcp_spec;
        pattern[2].mask = &tcp_mask;

        /* the final datablock_id must be always type end */
        pattern[3].type = RTE_FLOW_ITEM_TYPE_END;

        res = rte_flow_validate(0, &attr, pattern, action, &error);
        if (!res) {
            flow = rte_flow_create(0, &attr, pattern, action, &error);
        }

        if (!flow) {
            printf("Flow can't be created %d message: %s\n",
                   error.type,
                   error.message ? error.message : "(no stated reason)");
            rte_exit(EXIT_FAILURE, "error in creating flow");
        }
    }
}


void init_EAL(int argc, char *argv[]) {
    // initialize EAL
    int ret = rte_eal_init(argc, argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "Invalid EAL arguments\n");
}



void runtime_init(char *config_file) {
    c = rte_malloc(NULL, sizeof(struct Runtime_state), 0);
    // dump the available lcore ids
    for (int j = 0; j < RTE_MAX_LCORE; j++) {
        if (c->available_lcore[j]) {
            DEBUG_PRINT("lcore %d is available\n", j);
            // DEBUG_PRINT the physical core id of the lcore
            DEBUG_PRINT("lcore %d is on socket %d\n", j, rte_lcore_to_socket_id(j));
        }
    }
    // output the main lcore id
    DEBUG_PRINT("main lcore id is %d\n", rte_get_main_lcore());
    // make the main lcore id not available
    c->available_lcore[rte_get_main_lcore()] = false;
    // we assume that we have 16 queues
    c->queue_num = 1;
    c->hz = rte_get_timer_hz();
    DEBUG_PRINT("The number of cycles in one second is %lu\n", c->hz);

    c->cp_quit = false;
    c->ring_size = 1024;
    c->log_started = false;
}
