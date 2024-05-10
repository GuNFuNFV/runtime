

#ifndef NFLAMBDA_RUNTIME_AMF_H
#define NFLAMBDA_RUNTIME_AMF_H

#include "fsm_amac_nf_common.h"

struct amf_control_state {
    int reserved;
    int current_state;
    int prefetch_mode;
    EVENT unregistered;
    EVENT registered;
    EVENT context_setup;
    EVENT authentication;
    EVENT packet;
};

struct cache_line {
    uint8_t data[64];
} __attribute__((__packed__));

struct amf_data_state {
    struct cache_line cache_line[8];
};

static inline void operation_on_cache_line(struct cache_line *cache_line) {
    for (int i = 0; i < 8; i = i + 8) {
        cache_line->data[i]++;
    }
}

ACTOR_CONTROL_STATE_INIT(amf_init);
//"7":"amf_dispatcher","8":"amf_unregistered_handler","9":"amf_registered_handler","10":"amf_context_setup_handler","11":"amf_authentication_handler"
INLINE_ACTOR_ACTION(amf_dispatcher) {
    struct amf_control_state *amfControlState = (struct amf_control_state *) m->control_state;
    struct amf_data_state *amfDataState = (struct amf_data_state *) m->data_state;
    // dispatch to unregistered handler, registered handler, context_setup handler, authentication handler randomly
    amfControlState->current_state = (amfControlState->current_state + 1) % 4;
    int random = amfControlState->current_state;
    switch (amfControlState->prefetch_mode) {
        case 0: // only prefetch the corresponding cache lines
            if (random == 0) {
                m->event = amfControlState->unregistered;
                // prefetch the first cache line
                rte_prefetch0(&amfDataState->cache_line[0]);
            } else if (random == 1) {
                m->event = amfControlState->registered;
                // prefetch the first cache line and the second
                // cache line
                rte_prefetch0(&amfDataState->cache_line[0]);
                rte_prefetch0(&amfDataState->cache_line[1]);
                rte_prefetch0(&amfDataState->cache_line[2]);
            } else if (random == 2) {
                m->event = amfControlState->context_setup;
                // prefetch the first cache line
                rte_prefetch0(&amfDataState->cache_line[0]);
                // prefetch the third cache line
                rte_prefetch0(&amfDataState->cache_line[3]);
                rte_prefetch0(&amfDataState->cache_line[4]);
            } else if (random == 3) {
                m->event = amfControlState->authentication;
                // prefetch the first cache line
                rte_prefetch0(&amfDataState->cache_line[0]);
                // prefetch the fourth cache line
                rte_prefetch0(&amfDataState->cache_line[5]);
                rte_prefetch0(&amfDataState->cache_line[6]);
            }
            break;
        case 1: // prefetch all cache lines
            if (random == 0) {
                m->event = amfControlState->unregistered;
                // prefetch the first cache line
                rte_prefetch0(&amfDataState->cache_line[0]);
                rte_prefetch0(&amfDataState->cache_line[1]);
                rte_prefetch0(&amfDataState->cache_line[2]);
                rte_prefetch0(&amfDataState->cache_line[3]);
                rte_prefetch0(&amfDataState->cache_line[4]);
                rte_prefetch0(&amfDataState->cache_line[5]);
                rte_prefetch0(&amfDataState->cache_line[6]);
            } else if (random == 1) {
                m->event = amfControlState->registered;
                // prefetch the first cache line and the second cache line
                rte_prefetch0(&amfDataState->cache_line[0]);
                rte_prefetch0(&amfDataState->cache_line[1]);
                rte_prefetch0(&amfDataState->cache_line[2]);
                rte_prefetch0(&amfDataState->cache_line[3]);
                rte_prefetch0(&amfDataState->cache_line[4]);
                rte_prefetch0(&amfDataState->cache_line[5]);
                rte_prefetch0(&amfDataState->cache_line[6]);
            } else if (random == 2) {
                m->event = amfControlState->context_setup;
                rte_prefetch0(&amfDataState->cache_line[0]);
                rte_prefetch0(&amfDataState->cache_line[1]);
                rte_prefetch0(&amfDataState->cache_line[2]);
                rte_prefetch0(&amfDataState->cache_line[3]);
                rte_prefetch0(&amfDataState->cache_line[4]);
                rte_prefetch0(&amfDataState->cache_line[5]);
                rte_prefetch0(&amfDataState->cache_line[6]);
            } else if (random == 3) {
                m->event = amfControlState->authentication;
                rte_prefetch0(&amfDataState->cache_line[0]);
                rte_prefetch0(&amfDataState->cache_line[1]);
                rte_prefetch0(&amfDataState->cache_line[2]);
                rte_prefetch0(&amfDataState->cache_line[3]);
                rte_prefetch0(&amfDataState->cache_line[4]);
                rte_prefetch0(&amfDataState->cache_line[5]);
                rte_prefetch0(&amfDataState->cache_line[6]);
            }
            break;
        case 2: // no prefetch
            if (random == 0) {
                m->event = amfControlState->unregistered;
            } else if (random == 1) {
                m->event = amfControlState->registered;
            } else if (random == 2) {
                m->event = amfControlState->context_setup;
            } else if (random == 3) {
                m->event = amfControlState->authentication;
            }
            break;
        case 3: // non-temporal prefetch
            if (random == 0) {
                m->event = amfControlState->unregistered;
                // prefetch the first cache line
                rte_prefetch_non_temporal(&amfDataState->cache_line[0]);
            } else if (random == 1) {
                m->event = amfControlState->registered;
                // prefetch the first cache line and the second cache line
                rte_prefetch_non_temporal(&amfDataState->cache_line[0]);
                rte_prefetch_non_temporal(&amfDataState->cache_line[1]);
                rte_prefetch_non_temporal(&amfDataState->cache_line[2]);
            } else if (random == 2) {
                m->event = amfControlState->context_setup;
                // prefetch the first cache line
                rte_prefetch_non_temporal(&amfDataState->cache_line[0]);
                rte_prefetch_non_temporal(&amfDataState->cache_line[3]);
                rte_prefetch_non_temporal(&amfDataState->cache_line[4]);
            } else if (random == 3) {
                m->event = amfControlState->authentication;
                rte_prefetch_non_temporal(&amfDataState->cache_line[0]);
                rte_prefetch_non_temporal(&amfDataState->cache_line[5]);
                rte_prefetch_non_temporal(&amfDataState->cache_line[6]);
            }
    }

}

INLINE_ACTOR_ACTION(amf_unregistered_handler) {
    struct amf_control_state *amfControlState = (struct amf_control_state *) m->control_state;
    struct amf_data_state *amfDataState = (struct amf_data_state *) m->data_state;
    // operation on the first cache line
    operation_on_cache_line(&amfDataState->cache_line[0]);
    m->event = amfControlState->packet;
//    DEBUG_PRINT("amf_unregistered_handler\n");
}

INLINE_ACTOR_ACTION(amf_registered_handler) {
    struct amf_control_state *amfControlState = (struct amf_control_state *) m->control_state;
    struct amf_data_state *amfDataState = (struct amf_data_state *) m->data_state;
    // operation on the first cache line and the second cache line
    operation_on_cache_line(&amfDataState->cache_line[0]);
    operation_on_cache_line(&amfDataState->cache_line[1]);
    operation_on_cache_line(&amfDataState->cache_line[2]);
    m->event = amfControlState->packet;
//    DEBUG_PRINT("amf_registered_handler\n");
}

INLINE_ACTOR_ACTION(amf_context_setup_handler) {
    struct amf_control_state *amfControlState = (struct amf_control_state *) m->control_state;
    struct amf_data_state *amfDataState = (struct amf_data_state *) m->data_state;
    // operation on the first cache line and the third cache line
    operation_on_cache_line(&amfDataState->cache_line[0]);
    operation_on_cache_line(&amfDataState->cache_line[3]);
    operation_on_cache_line(&amfDataState->cache_line[4]);
    m->event = amfControlState->packet;
//    DEBUG_PRINT("amf_context_setup_handler\n");
}

INLINE_ACTOR_ACTION(amf_authentication_handler) {
    struct amf_control_state *amfControlState = (struct amf_control_state *) m->control_state;
    struct amf_data_state *amfDataState = (struct amf_data_state *) m->data_state;
    // operation on the first cache line and the fourth cache line
    operation_on_cache_line(&amfDataState->cache_line[0]);
    operation_on_cache_line(&amfDataState->cache_line[5]);
    operation_on_cache_line(&amfDataState->cache_line[6]);
    m->event = amfControlState->packet;
//    DEBUG_PRINT("amf_authentication_handler\n");
}


#endif //NFLAMBDA_RUNTIME_AMF_H
