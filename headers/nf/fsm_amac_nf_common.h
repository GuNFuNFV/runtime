
#ifndef NFLAMBDA_RUNTIME_FSM_AMAC_NF_COMMON_H
#define NFLAMBDA_RUNTIME_FSM_AMAC_NF_COMMON_H

#include "stdint.h"
#include "stddef.h"
#include "basic_operation.h"
#include "worker/worker_amac_nflow.h"


struct amac_nf_init_option {
    char name[100];
};

enum HEADER_TYPE {
    FIVE_TUPLE, SRC_IP
};

typedef uint8_t CONTROL_VARIABLE_OFFSET;
static inline void increment_n_byte_data(void* data, size_t n);


#include "nf/control_state/worker_amac_nf_path.h"
#include "worker/message.h"
#include "worker/worker_amac_classifier.h"
#include "worker/worker_amac_control_state.h"
#include "worker/worker_amac.h"
#include "worker/worker_amac_thread.h"
#include "debug.h"
#include "rte_hash.h"
#include "data_operation.h"


#endif //NFLAMBDA_RUNTIME_FSM_AMAC_NF_COMMON_H
