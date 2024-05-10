//
// Created by ziyan on 8/20/23.
//

#ifndef NFLR_FASTCLICK_LB_H
#define NFLR_FASTCLICK_LB_H

#include "fsm_amac_nf_common.h"
#include "rte_ether.h"

struct LBControlState {
    rte_be32_t *destination_ip_list;
    EVENT packet;
};


ACTOR_CONTROL_STATE_INIT(fastclick_lb_init);

INLINE_ACTOR_ACTION(fastclick_lb) {
    // porting the implementation from NAT::DoProcessBatch
    struct LBControlState *pLbControlState = (struct LBControlState *) m->control_state;
    // get the packet
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    struct rte_tcp_hdr *tcp_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_tcp_hdr*,
                                                          sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));

    struct five_tuple temp_fiveTuple;
    temp_fiveTuple.src_ip = ipv4_hdr->src_addr;
    temp_fiveTuple.dst_ip = ipv4_hdr->dst_addr;
    uint32_t result = pLbControlState->destination_ip_list[rte_be_to_cpu_32(temp_fiveTuple.src_ip)];
    tcp_hdr->dst_port = result;
//    DEBUG_PRINT("fastclick_lb: %u\n", result);
    m->event = pLbControlState->packet;
}


#endif //NFLR_FASTCLICK_LB_H
