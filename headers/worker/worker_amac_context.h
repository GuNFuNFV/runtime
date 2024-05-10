
#ifndef NFLAMBDA_RUNTIME_WORKER_AMAC_CONTEXT_H
#define NFLAMBDA_RUNTIME_WORKER_AMAC_CONTEXT_H

#include "stdbool.h"
#include "multi_level_state.h"
#include "worker_amac_actor_table.h"
#include "worker_amac_control_state.h"
#include "worker_amac_task.h"

struct worker_amac_context {
    int core_id;
    int queue_id;
    int tx_port_id;
    int rx_port_id;
    int num_interleaved_threads;
    int initial_actor;

    int worker_destination_instance; // default
    struct worker_actor_table actorTable;
    struct worker_control_state_table controlStateTable;
    struct amac_task_table amacTaskTable;
    struct rte_mempool *mbuf_pool;
    // tx buffer
    struct rte_eth_dev_tx_buffer *tx_buffer;
    bool running;
    bool tx_mode;
    long total_packet;

    // state management in the data plane
    void **datablock[20]; // state in the data plane; could be the pointer to the classifier or the per-flow state itself
    // each element is a pointer to the datablock which stores the state
    size_t entry_size[20]; // size of the state in the data plane
    size_t total_entries_n[20]; // number of entries in the state in the data plane
    size_t num_flow_differentiated_per_entry[20]; // number of entries in each bucket in the state in the data plane

    // used by traffic generator
    int batch_size; // used by traffic generator
    struct rte_mbuf **mbuf[1024]; // used by traffic generator
};

#define AMAC_WORKER_INIT(name) char *name(struct worker_amac_context *pStructworkerAmacContext, char **tokens, char *out, size_t out_size)

typedef AMAC_WORKER_INIT((*AMAC_WORKER_INIT_PTR));

#include "stdbool.h"

#endif //NFLAMBDA_RUNTIME_WORKER_AMAC_CONTEXT_H
