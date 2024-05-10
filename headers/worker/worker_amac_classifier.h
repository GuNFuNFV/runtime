

#ifndef NFLAMBDA_RUNTIME_WORKER_AMAC_CLASSIFIER_H
#define NFLAMBDA_RUNTIME_WORKER_AMAC_CLASSIFIER_H
#include "worker_amac_macro.h"
#define AMAC_CLASSIFIER_INIT(name) void *name(void* control_state, int num_flow, int core_id, int datablock_id)
typedef AMAC_CLASSIFIER_INIT((*AMAC_CLASSIFIER_INIT_PTR));

//AMAC_WORKER_INIT(worker_fsm_amac_classifier_init);

#endif //NFLAMBDA_RUNTIME_WORKER_AMAC_CLASSIFIER_H
