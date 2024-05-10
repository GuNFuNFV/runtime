
#ifndef NFLAMBDA_RUNTIME_AMAC_MESSAGE_H
#define NFLAMBDA_RUNTIME_AMAC_MESSAGE_H

#include <nf/control_state/worker_amac_nf_path.h>
#include "stdint.h"
#include "stddef.h"
#include "rte_mbuf.h"
#include "nf/control_state/controlstate_bessnat.h"


struct temporary_state_buffer{
    uint8_t data[100];
};

struct message{
    struct temporary_state_buffer buffer;
    struct rte_mbuf* packet; // packets that need to be processed
    void* control_state; // the state of the actor, initialized in the beginning
    void* data_state; // the classifier_state of the actor, installed by the worker thread depending on the current datablock_id
    EVENT event; // event has many-to-one mapping to the actors that need to process the event
    struct rte_eth_dev_tx_buffer *tx_buffer;
    int port_id;
    int queue_id;

    int datablock_id; // the current data block datablock_id
    int global_offset[5];
    int local_offset[5];
    int bucket_id[5];
};


#define ACTOR_ACTION(name) void name(struct message* m)
#define INLINE_ACTOR_ACTION(name) static inline void name(struct message* m)
typedef ACTOR_ACTION((*ACTOR_ACTION_PTR));



// C-like DSL for actor actions
#define EMIT_EVENT(NEW_EVENT) \
    do { \
        m->event = ControlState->NEW_EVENT; \
    } while (0)

#define BEGIN_ACTOR_ACTION { GET_CONTROL_STATE;

#define NF_ACTOR_ACTION(name) static inline void name(struct message* m) { \
    BEGIN_ACTOR_ACTION
//#define END_ACTOR_ACTION() }
#endif //NFLAMBDA_RUNTIME_AMAC_MESSAGE_H
