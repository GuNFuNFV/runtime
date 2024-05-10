
#ifndef NFLAMBDA_RUNTIME_WORKER_AMAC_H
#define NFLAMBDA_RUNTIME_WORKER_AMAC_H
#include "key.h"
#include "stdint.h"
#include "rte_mbuf.h"
#include "rte_malloc.h"
#include "rte_ip.h"
#include "rte_tcp.h"
#include "debug.h"
#include "message.h"
#include "parse_config.h"
#include "worker_amac_context.h"
#include "multi_level_state.h"
#include "worker_amac_control_state.h"
#include "worker_amac_actor_table.h"
#include "worker_amac_task.h"
#include "worker_amac_thread.h"
#include "nf/fsm_amac_nf_lib.h"
#include "worker_amac_classifier.h"
#include "worker_amac_macro.h"

AMAC_WORKER_INIT(init_worker_amac_context);
AMAC_WORKER_INIT(control_state_init);
AMAC_WORKER_INIT(worker_actor_table_init);
AMAC_WORKER_INIT(actor_control_state_association);
AMAC_WORKER_INIT(worker_fsm_amac_run);
AMAC_WORKER_INIT(worker_fsm_amac_install_nflow);
AMAC_WORKER_INIT(worker_fsm_amac_total_packet);
AMAC_WORKER_INIT(control_state_configure);
AMAC_WORKER_INIT(actor_datablock_association);
AMAC_WORKER_INIT(init_datablock);

AMAC_WORKER_INIT(worker_actor_entry_event);

struct data_block_options_init{
    char name[100];
    AMAC_CLASSIFIER_INIT_PTR init;
    size_t size;
};

#endif //NFLAMBDA_RUNTIME_WORKER_AMAC_H
