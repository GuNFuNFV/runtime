#ifndef NFLAMBDA_RUNTIME_TRAFFIC_GENERATOR_SINK_H
#define NFLAMBDA_RUNTIME_TRAFFIC_GENERATOR_SINK_H

#include "control_state/controlstate_traffic_generator_sink.h"
#include "fsm_amac_nf_common.h"


//#include "json_helper.h"
ACTOR_CONTROL_STATE_INIT(traffic_generator_sink_init);

static int times = 0;
INLINE_ACTOR_ACTION(traffic_generator_sink) {
    struct trafic_generator_sink_control_state *TGSC = (struct trafic_generator_sink_control_state *) m->control_state;
    struct rte_tcp_hdr *tcp_hdr;
    tcp_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_tcp_hdr*,
                                      sizeof(struct rte_ipv4_hdr) + sizeof(struct rte_ether_hdr));
//    uint32_t lower_32 = (uint32_t)(tsc_value & 0xFFFFFFFF);
//    uint32_t higher_32 = (uint32_t)((tsc_value >> 32) & 0xFFFFFFFF);
//
//    // Store them in the TCP header's sent_seq and recv_ack fields:
//    tcp_hdr->sent_seq = rte_cpu_to_be_32(lower_32);   // Convert to big endian
//    tcp_hdr->recv_ack = rte_cpu_to_be_32(higher_32);  // Convert to big endian

    uint32_t lower_32 = (tcp_hdr->sent_seq);
    uint32_t higher_32 = (tcp_hdr->recv_ack);
    uint64_t tsc_value = ((uint64_t) higher_32 << 32) | lower_32;
    // get the current time
    uint64_t current_time = rte_rdtsc_precise();
    // get the time difference
    uint64_t time_diff = current_time - tsc_value;
    // get the time difference in us
    uint64_t time_diff_us = (double) time_diff / (rte_get_tsc_hz()/ 1000000);
    TGSC->latency_store[TGSC->current_latency_store_index] = time_diff_us;
    TGSC->current_latency_store_index = (TGSC->current_latency_store_index + 1) % LATENCY_STORE_SIZE;
    // if times = 100000, write the latency to file
    times++;
    if (times == 1000000) {
        times = 0;
        FILE *fp = fopen("/home/ziyan/latency.txt", "w");
        if (fp == NULL) {
            printf("open file failed\n");
            return;
        }
        for (int i = 0; i < 100; i++) {
            fprintf(fp, "%lu\n", TGSC->latency_store[i]);
        }
        fclose(fp);
    }
    m->event = TGSC->packet;
}

#endif //NFLAMBDA_RUNTIME_TRAFFIC_GENERATOR_SINK_H
