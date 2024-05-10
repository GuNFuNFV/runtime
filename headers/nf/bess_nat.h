#ifndef NFLR_BESS_NAT_H
#define NFLR_BESS_NAT_H

#include "fsm_amac_nf_common.h"
#include "rte_ether.h"
#include "control_state/controlstate_bessnat.h"

#define GET_CONTROL_STATE \
    struct NATControlState *ControlState = (struct NATControlState *) m->control_state

ACTOR_CONTROL_STATE_INIT(bess_nat_init);
// template <NAT::Direction dir>
//inline void NAT::DoProcessBatch(Context *ctx, bess::PacketBatch *batch) {
//  gate_idx_t ogate_idx = dir == kForward ? 1 : 0;
//  int cnt = batch->cnt();
//  uint64_t now = ctx->current_ns;
//
//  for (int i = 0; i < cnt; i++) {
//    bess::Packet *pkt = batch->pkts()[i];
//
//    Ethernet *eth = pkt->head_data<Ethernet *>();
//    Ipv4 *ip = reinterpret_cast<Ipv4 *>(eth + 1);
//    size_t ip_bytes = (ip->header_length) << 2;
//    void *l4 = reinterpret_cast<uint8_t *>(ip) + ip_bytes;
//
//    bool valid_protocol;
//    Endpoint before;
//    std::tie(valid_protocol, before) = ExtractEndpoint(ip, l4, dir);
//
//    if (!valid_protocol) {
//      DropPacket(ctx, pkt);
//      continue;
//    }
//
//    auto *hash_item = map_.Find(before);
//
//    if (hash_item == nullptr) {
//      if (dir != kForward || !(hash_item = CreateNewEntry(before, now))) {
//        DropPacket(ctx, pkt);
//        continue;
//      }
//    }
//
//    // only refresh for outbound packets, rfc4787 REQ-6
//    if (dir == kForward) {
//      hash_item->second.last_refresh = now;
//    }
//
//    Stamp<dir>(ip, l4, before, hash_item->second.endpoint);
//    EmitPacket(ctx, pkt, ogate_idx);
//  }
//}

INLINE_ACTOR_ACTION(bess_nat) {
    // porting the implementation from NAT::DoProcessBatch
    GET_CONTROL_STATE;
    // get the packet
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    struct rte_tcp_hdr *tcp_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_tcp_hdr*,
                                                          sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));

//    DEBUG_PRINT("source ip: %u, source port: %u, destination ip: %u, destination port: %u\n",
//           ipv4_hdr->src_addr, tcp_hdr->src_port, ipv4_hdr->dst_addr, tcp_hdr->dst_port);
    // try to lookup it up in the nat table
    struct five_tuple temp_fiveTuple;
    temp_fiveTuple.src_ip = ipv4_hdr->src_addr;
    temp_fiveTuple.src_port = 0;
    temp_fiveTuple.dst_ip = ipv4_hdr->dst_addr;
    temp_fiveTuple.dst_port =  0;
    int ret = rte_hash_lookup_data(ControlState->nat_table, &temp_fiveTuple, (void **) &temp_fiveTuple);
    if (ret < 0) {
        // not found, create a new entry
//        DEBUG_PRINT("not found, create a new entry\n");
//        DEBUG_PRINT("src ip %u, dst ip %u\n", rte_be_to_cpu_32(temp_fiveTuple.src_ip), rte_be_to_cpu_32(temp_fiveTuple.dst_ip));
    } else {
        uint32_t result = ControlState->destination_ip_list[ret];
        ipv4_hdr->dst_addr = result;
//        DEBUG_PRINT("result: %u\n", result);
    }


    EMIT_EVENT(packet);
}


#endif //NFLR_BESS_NAT_H
