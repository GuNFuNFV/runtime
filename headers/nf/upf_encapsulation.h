
#ifndef NFLAMBDA_RUNTIME_UPF_ENCAPSULATOR_H
#define NFLAMBDA_RUNTIME_UPF_ENCAPSULATOR_H



#include "fsm_amac_nf_common.h"
#include "common.h"
#include "stdint-gcc.h"
#include "stdbool.h"
#include "stdio.h"


struct upf_encapsulator_state {
    EVENT packet;
};

struct upf_data_state {
    struct five_tuple five_tuple;
};

INLINE_ACTOR_ACTION(upf_encapsulate) {
    struct upf_encapsulator_state *upfControlState = (struct upf_encapsulator_state *) m->control_state;
    struct upf_data_state *upfDataState = (struct upf_data_state *) m->data_state;
    // read the five tuple from the data state
    struct five_tuple *five_tuple = &upfDataState->five_tuple;
    // encapsulate the packet by removing the ethernet header and adding the gtp header, udp header, ip header, and ethernet header
    struct rte_mbuf *pkt = m->packet;
    struct rte_ether_hdr *eth_hdr = rte_pktmbuf_mtod(pkt, struct rte_ether_hdr *);
    struct rte_ipv4_hdr *ip_hdr = (struct rte_ipv4_hdr *) (eth_hdr + 1);
    // remove the ethernet header
    rte_pktmbuf_adj(pkt, sizeof(struct rte_ether_hdr));
    // add the gtp header, udp header, ip header, and ethernet header
    int added_len = sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr) + sizeof(struct rte_udp_hdr) +
                    sizeof(struct rte_gtp_hdr);
    rte_pktmbuf_prepend(pkt, added_len);
    // get the outer ip header
    struct rte_ipv4_hdr *outer_ip_hdr = rte_pktmbuf_mtod(pkt, struct rte_ipv4_hdr *);
    outer_ip_hdr->version_ihl = 0x45;
    outer_ip_hdr->type_of_service = 0;
    outer_ip_hdr->src_addr = five_tuple->src_ip;
    outer_ip_hdr->dst_addr = five_tuple->dst_ip;
    m->event = upfControlState->packet;
}

ACTOR_CONTROL_STATE_INIT(upf_encapsulation_init);

#endif //NFLAMBDA_RUNTIME_UPF_ENCAPSULATOR_H