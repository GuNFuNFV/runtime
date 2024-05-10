

#ifndef MULTICORE_FWDING_DPDK_CONFIG_H
#define MULTICORE_FWDING_DPDK_CONFIG_H

#include "common.h"
#include "port.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <rte_timer.h>
#include "rte_cycles.h"
#include <bits/types/FILE.h>
#include <stdlib.h>
#include <sys/io.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <inttypes.h>
#include <unistd.h>
#include "worker/worker_amac.h"
#define IP_DEFTTL  64   /* from RFC 1340. */
#define IP_VERSION 0x40
#define IP_HDRLEN  0x05 /* default IP header complexity == five 32-bits words. */
#define IP_VHL_DEF (IP_VERSION | IP_HDRLEN)
#define NF_NUM 2

// max number of worker is max number of cores
#define MAX_WORKER_NUM 48


struct action_descriptor {
    int action_id;

    void (*action)(struct state *, struct message *);
};

struct worker {
    enum worker_state *state;
    int queue_num;
    int tx_port_id;
    long rxn; // number of packets recieved

    long operations_n;
    bool dp_quit;
    /// needs to be configured by the director
    // worker ip address
    uint32_t ip;
    struct rte_mempool *packet_pool;
    struct rte_mempool *msg_pool;
    void *states;
};

struct Runtime_state {
    int max_pkt_burst;
    int mbuf_cache_size;
    int num_mbufs;
    uint16_t nb_rxd;
    uint16_t nb_txd;
    struct port_parameter *portParameter;
    uint64_t hz;
    volatile bool cp_quit;
    volatile bool log_option;

    int ring_size;

    struct rte_eth_dev_info info;
//    struct rte_eth_rss_reta_entry64 reta_conf[RSS_I_TABLE_SIZE / RTE_RETA_GROUP_SIZE]; // bucket_to_queue_id
    struct rte_eth_rss_reta_entry64 reta_conf; // bucket_to_queue_id
    int queue_num;

    uint64_t p_time;
    bool log_started;

    bool running;
    bool available_lcore[RTE_MAX_LCORE];

    /////////*****/////////
    struct worker_amac_context worker_amac_context_list[RTE_MAX_LCORE];

};

void init_EAL(int argc, char *argv[]);

void runtime_init(char *config_file);

void install_flow();

void initialize_worker(struct Runtime_state *c);

void initialize_action_table(struct rte_hash_table **action_table);

void output_log(struct Runtime_state *c);


#endif //MULTICORE_FWDING_DPDK_CONFIG_H