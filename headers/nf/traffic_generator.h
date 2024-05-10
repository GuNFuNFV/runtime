
#ifndef NFLAMBDA_RUNTIME_TRAFFIC_GENERATOR_H
#define NFLAMBDA_RUNTIME_TRAFFIC_GENERATOR_H

#include "fsm_amac_nf_common.h"
#include "control_state/controlstate_traffic_generator.h"


ACTOR_CONTROL_STATE_INIT(traffic_generator_init);

ACTOR_CONTROL_STATE_CONFIGURE(traffic_generator_configure);


INLINE_ACTOR_ACTION(traffic_generator) {
//    DEBUG_PRINT("traffic_generator_send_packet\n");
    struct traffic_generator_state *traffic_generator_state = (struct traffic_generator_state *) m->control_state;
    // allocate mbuf from the mbuf pool
    struct rte_ether_hdr *eth_hdr;
    struct rte_ipv4_hdr *ipv4_hdr;
    struct rte_tcp_hdr *tcp_hdr;
    struct rte_mbuf *pmbuf;
    struct rte_mbuf **mbuf = traffic_generator_state->mbuf;
    int batch_size = 32;
    int total_proportion = traffic_generator_state->total_proportion;

    int pass = batch_size / total_proportion + 1;
    int last_pass = batch_size % total_proportion;
    int current_packet = 0;
    for (int i = 0; i < pass; i++) {
        int num_packet = total_proportion;
        if (i == pass - 1) {
            num_packet = last_pass;
        }
        for (int j = 0; j < num_packet; j++) {
            // get the traffic class
            int traffic_class_id = traffic_generator_state->scheduling_slots[rte_rand_max(
                    traffic_generator_state->total_proportion)];
            struct traffic_generator_traffic_class *traffic_class = &traffic_generator_state->traffic_class[traffic_class_id];
            // get the destination instance
            int destination_instance = traffic_class->destination_instance;
            // get the flow id
            int flow_id = rte_rand_max(traffic_class->flow_id_upper - traffic_class->flow_id_lower) +
                          traffic_class->flow_id_lower;
            // get the subflow id
            int subflow_id = rte_rand_max(traffic_class->subflow_id_upper - traffic_class->subflow_id_lower) +
                             traffic_class->subflow_id_lower;
            // get the packet size
            int packet_size = traffic_class->packet_size;
            int core_id = traffic_generator_state->core_id;
            // get the mbuf
            pmbuf = mbuf[current_packet++];
            // get the ip header and tcp header
            eth_hdr = rte_pktmbuf_mtod(pmbuf, struct rte_ether_hdr*);
            ipv4_hdr = rte_pktmbuf_mtod_offset(pmbuf, struct rte_ipv4_hdr*, sizeof(struct rte_ether_hdr));
            tcp_hdr = rte_pktmbuf_mtod_offset(pmbuf, struct rte_tcp_hdr*,
                                              sizeof(struct rte_ipv4_hdr) + sizeof(struct rte_ether_hdr));
            eth_hdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);
            ipv4_hdr->src_addr = rte_cpu_to_be_32(flow_id);
            ipv4_hdr->dst_addr = rte_cpu_to_be_32(core_id + destination_instance);
            ipv4_hdr->next_proto_id = IPPROTO_TCP;
            tcp_hdr->src_port = rte_cpu_to_be_16(subflow_id);
            tcp_hdr->dst_port = rte_cpu_to_be_16(0);
            // current timestamp to dst_port
            // get the current timesteamp
            uint64_t tsc_value = rte_rdtsc();
            uint32_t lower_32 = (uint32_t) (tsc_value & 0xFFFFFFFF);
            uint32_t higher_32 = (uint32_t) ((tsc_value >> 32) & 0xFFFFFFFF);

            // Store them in the TCP header's sent_seq and recv_ack fields:
            tcp_hdr->sent_seq = (lower_32);   // Convert to big endian
            tcp_hdr->recv_ack = (higher_32);  // Convert to big endian
            // set the packet size
            pmbuf->pkt_len = packet_size;
            pmbuf->data_len = packet_size;
        }
    }
    int sent;

    sent = rte_eth_tx_burst(traffic_generator_state->port_id, traffic_generator_state->queue_id, mbuf, batch_size);
    // send the packet until all the packets are sent
    if (sent < batch_size) {
        // drop the packet
        rte_pktmbuf_free_bulk(&mbuf[sent], batch_size - sent);
    }
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();
//    rte_pause();


    traffic_generator_state->worker_amac_context->total_packet += sent;
}

#endif //NFLAMBDA_RUNTIME_TRAFFIC_GENERATOR_H
