

#ifndef NFLAMBDA_RUNTIME_PASSTHROUGH_H
#define NFLAMBDA_RUNTIME_PASSTHROUGH_H

#include "fsm_amac_nf_common.h"

struct passthrough_context {
    EVENT packet;
};

ACTOR_CONTROL_STATE_INIT(passthrough_init);

INLINE_ACTOR_ACTION(passthrough) {
//    DEBUG_PRINT("In passthrough action\n");
    struct passthrough_context *ctx = m->control_state;
    m->event = ctx->packet;
}

#endif //NFLAMBDA_RUNTIME_PASSTHROUGH_H
