#ifndef NFLAMBDA_RUNTIME_SYSTEM_ACTION_H
#define NFLAMBDA_RUNTIME_SYSTEM_ACTION_H

#include "worker/worker_amac_context.h"
#include "fsm_amac_nf_common.h"

INLINE_ACTOR_ACTION(receive_packet) {

}

INLINE_ACTOR_ACTION(send_packet) {
    struct worker_amac_context *ctx = (struct worker_amac_contextZ *) m->control_state;
    int destination_instance = ctx->worker_destination_instance;
    int core_id = ctx->core_id;
    struct rte_ether_hdr *eth_hdr;
    struct rte_ipv4_hdr *ipv4_hdr;
    ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*, sizeof(struct rte_ether_hdr));
    ipv4_hdr->dst_addr = rte_cpu_to_be_32(core_id + destination_instance);
    int ret = rte_eth_tx_buffer(ctx->rx_port_id, ctx->queue_id, m->tx_buffer, m->packet);

//    rte_eth_tx_burst(ctx->rx_port_id, ctx->queue_id, &m->packet, 1);
    m->event = 255;
}

INLINE_ACTOR_ACTION(drop) {
//    DEBUG_PRINT("drop\n");
    rte_mbuf_raw_free(m->packet);
    m->event = 255;
}

INLINE_ACTOR_ACTION(Exit) {
    DEBUG_PRINT("exit\n");
    exit(0);
}

#endif //NFLAMBDA_RUNTIME_SYSTEM_ACTION_H
