#ifndef NFLR_CONTROLSTATE_TRAFFIC_GENERATOR_SINK_H
#define NFLR_CONTROLSTATE_TRAFFIC_GENERATOR_SINK_H

#include "stdint-gcc.h"
#include "worker_amac_nf_path.h"

#define LATENCY_STORE_SIZE 1000

struct trafic_generator_sink_control_state {
    uint64_t latency_store[LATENCY_STORE_SIZE]; // store the latency of each packet
    int current_latency_store_index; // the index of the current latency store
    EVENT packet;
};

#endif //NFLR_CONTROLSTATE_TRAFFIC_GENERATOR_SINK_H
