#ifndef NFLR_TRAFFIC_GENERATOR_H
#define NFLR_TRAFFIC_GENERATOR_H
#include "worker_amac_nf_path.h"
#include "rte_ether.h"

struct traffic_generator_traffic_class {
    int destination_instance;
    int flow_id_lower;
    int flow_id_upper;
    int packet_size;
    int proportion;
    int subflow_id_lower;
    int subflow_id_upper;
};


#define MAX_TRAFFIC_CLASS_NUM 10
struct traffic_generator_state {
    int traffic_class_num;
    int core_id; // core id of the traffic generator
    int port_id;
    int queue_id;
    struct traffic_generator_traffic_class traffic_class[MAX_TRAFFIC_CLASS_NUM];
    struct rte_mbuf **mbuf;
    int batch_size;
    EVENT packet;
    struct worker_amac_context *worker_amac_context;
    int scheduling_slots[300];
    int total_proportion;
};


#endif