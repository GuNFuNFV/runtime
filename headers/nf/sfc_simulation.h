#ifndef NFLR_SFC_SIMULATION_ACTION_H
#define NFLR_SFC_SIMULATION_ACTION_H

#include "control_state/controlstate_sfc_simulation.h"
#include "fsm_amac_nf_common.h"


ACTOR_CONTROL_STATE_INIT(sfc_simulation_init);

INLINE_ACTOR_ACTION(prefetch_action) {
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) m->control_state;
    void*data_state = m->data_state;
    int sfc_length = context->sfc_length;
    int data_packing = context->datapacking;
    DEBUG_PRINT("prefetch_action\n");
    // prefetch the the first cache line
    rte_prefetch0(data_state);
    m->event = context->first_action;
}

INLINE_ACTOR_ACTION(first_action) {
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    int sfc_length = context->sfc_length;
    int data_packing = context->datapacking;
    DEBUG_PRINT("first_action\n");
    write_variable(m->data_state, 8);
    ipv4_hdr->dst_addr = *(uint32_t*) m->data_state;
    if (sfc_length < 2) {
        DEBUG_PRINT("sfc_length<1\n");
        m->event = context->packet;
        return;
    }

    m->event = context->second_action;
}

INLINE_ACTOR_ACTION(second_action) {
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    int sfc_length = context->sfc_length;
    int data_packing = context->datapacking;
    DEBUG_PRINT("second_action\n");
    write_variable(m->data_state + 8, 8);
    ipv4_hdr->dst_addr = *(uint32_t*) m->data_state + 8;

    if (sfc_length < 3) {
        DEBUG_PRINT("sfc_length<2\n");
        m->event = context->packet;
        return;
    }
    m->event = context->third_action;
}

INLINE_ACTOR_ACTION(third_action) {
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    int sfc_length = context->sfc_length;
    int data_packing = context->datapacking;
    DEBUG_PRINT("third_action\n");
    write_variable(m->data_state + 16, 8);
    ipv4_hdr->dst_addr = *(uint32_t*) m->data_state + 16;
    if (sfc_length < 4) {
        DEBUG_PRINT("sfc_length<3\n");
        m->event = context->packet;
        return;
    }
    m->event = context->fourth_action;
}

INLINE_ACTOR_ACTION(fourth_action) {
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    int sfc_length = context->sfc_length;
    int data_packing = context->datapacking;
    DEBUG_PRINT("fourth_action\n");
    write_variable(m->data_state + 24, 8);
    ipv4_hdr->dst_addr = *(uint32_t*) m->data_state + 24;
    if (sfc_length < 5) {
        DEBUG_PRINT("sfc_length<4\n");
        m->event = context->packet;
        return;
    }
    m->event = context->fifth_action;
}

INLINE_ACTOR_ACTION(fifth_action) {
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    int sfc_length = context->sfc_length;
    int data_packing = context->datapacking;
    DEBUG_PRINT("fifth_action\n");
    write_variable(m->data_state + 32, 8);
    ipv4_hdr->dst_addr = *(uint32_t*) m->data_state + 32;
    if (sfc_length < 6) {
        DEBUG_PRINT("sfc_length<5\n");
        m->event = context->packet;
        return;
    }
    m->event = context->sixth_action;
}

INLINE_ACTOR_ACTION(sixth_action) {
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) m->control_state;
    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(m->packet, struct rte_ipv4_hdr*,
                                                            sizeof(struct rte_ether_hdr));
    int sfc_length = context->sfc_length;
    int data_packing = context->datapacking;
    DEBUG_PRINT("sixth_action\n");
    write_variable(m->data_state + 40, 8);
    ipv4_hdr->dst_addr = *(uint32_t*) m->data_state + 40;
    m->event = context->packet;
}


#endif //NFLR_SFC_SIMULATION_H
