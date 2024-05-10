#ifndef NFLAMBDA_RUNTIME_WORKER_AMAC_THREAD_H
#define NFLAMBDA_RUNTIME_WORKER_AMAC_THREAD_H
#define BATCH_SIZE 128

#include "worker_amac.h"
#include "worker_amac_context.h"
#include "rte_ethdev.h"

static inline void
initiliaze_amac_task(struct nftask *task, struct worker_amac_context *context, struct rte_mbuf **pkts, int i) {
    task->amacMessage.event = context->initial_actor;
    task->amacMessage.packet = pkts[i];
    task->amacMessage.local_offset[0] = 0;
    task->amacMessage.global_offset[0] = 0;
    task->amacMessage.datablock_id = context->actorTable.actor[context->initial_actor].datablock_id;
    task->amacMessage.tx_buffer = context->tx_buffer;
    task->amacMessage.port_id = context->rx_port_id;
    task->amacMessage.queue_id = context->queue_id;
    task->stage = 0;
    task->datablock_id = 0;
    task->done = false;

}

static void handle_entry_event(const struct worker_amac_context *context, struct message *amacMessage, int actor_id,
                   enum ENTRY_EVENT entryEvent) {
    int datablock_id;
    size_t local_offset;
    size_t bucket_id;
    size_t entry_size;
    size_t num_flow_differentiated_per_entry;
    size_t offset;
    switch (entryEvent) {
        case LOAD_PERFLOW_STATE:
            datablock_id = context->actorTable.actor[actor_id].datablock_id;
            local_offset = amacMessage->local_offset[datablock_id];
            bucket_id = amacMessage->global_offset[datablock_id - 1];
            entry_size = context->entry_size[datablock_id];
            num_flow_differentiated_per_entry = context->num_flow_differentiated_per_entry[datablock_id - 1];
            offset = local_offset;
            // assign context->datablock[datablock_id] plus offset * entry_size bytes to amacMessage->data_state
            amacMessage->data_state = (void *) ((char *) context->datablock[datablock_id] + offset * entry_size);
            amacMessage->control_state = context->actorTable.actor[actor_id].control_state;
            amacMessage->datablock_id = datablock_id;
            break;
        case LOAD_CLASSIFIER_STATE:
            datablock_id = context->actorTable.actor[actor_id].datablock_id;
            local_offset = amacMessage->local_offset[datablock_id];
            entry_size = context->entry_size[datablock_id];
            void** data_state = (void *) ((char *) context->datablock[datablock_id] + local_offset * entry_size);
            amacMessage->data_state = *data_state;
            amacMessage->control_state = context->actorTable.actor[actor_id].control_state;
            amacMessage->datablock_id = datablock_id;
            break;
        case LOAD_CONTROL_STATE:
        case ENTRY_POINT_DO_NOTHING:
            amacMessage->control_state = context->actorTable.actor[actor_id].control_state;
            break;
    }
}

static inline void worker_fsm_amac_thread(struct worker_amac_context *context) {
    DEBUG_PRINT("worker_fsm_amac_thread start\n");
    printf("worker id: %d\n", context->core_id);
    printf("queue id: %d\n", context->queue_id);

    if (context->tx_mode) {
        DEBUG_PRINT("tx mode\n");
        struct message msg;
        // get the initial state
        uint8_t state_id = context->initial_actor;
        if (context->mbuf_pool == NULL) {
            printf("mbuf pool is null\n");
            exit(1);
        }

        rte_pktmbuf_alloc_bulk(context->mbuf_pool, context->mbuf, context->batch_size);
        // get the control state
        uint8_t control_state_id = context->actorTable.actor[state_id].control_state_id;
        void *control_state = context->controlStateTable.control_state[control_state_id].control_state;
        msg.control_state = control_state;
        // run the action
        while (1)
            context->actorTable.actor[state_id].run(&msg);
    } else {
        printf("rx mode\n");
    }

    int batch_size = 32; // seems to be optimal?
    // receive some packets
    struct rte_mbuf *pkts[4096];
    int num_pkts;
    int current_packet;
    int current_task;
    uint64_t prev_tsc, diff_tsc, cur_tsc;
    uint64_t stuck_tsc = 0;
    const uint64_t drain_tsc = (rte_get_tsc_hz() + US_PER_S - 1);
    while (context->running) {
        if (context->tx_buffer->length > batch_size) {
            rte_eth_tx_buffer_flush(context->rx_port_id, context->queue_id, context->tx_buffer);
        }
        num_pkts = rte_eth_rx_burst(context->rx_port_id, context->queue_id, pkts, batch_size);
        while (num_pkts < batch_size) {
            num_pkts += rte_eth_rx_burst(context->rx_port_id, context->queue_id, pkts + num_pkts, batch_size);
        }
        context->total_packet += num_pkts;
        for (int i = 0; i < context->num_interleaved_threads; i++) {
            initiliaze_amac_task(&context->amacTaskTable.amacTask[i], context, pkts, i);
        }
        current_packet = context->num_interleaved_threads;
        context->amacTaskTable.current_task = 0;
        while (current_packet != num_pkts) {
            // deal with the current task
            current_task = context->amacTaskTable.current_task;
            struct nftask *amacTask = &context->amacTaskTable.amacTask[current_task];
            struct message *amacMessage = &amacTask->amacMessage;
            int actor_id = amacMessage->event;
            enum ENTRY_EVENT entryEvent = context->actorTable.actor[actor_id].entry_event;
            handle_entry_event(context, amacMessage, actor_id, entryEvent);
            context->actorTable.actor[actor_id].run(amacMessage);
            if (amacMessage->event == 255) {
                // reinitialize the task
                initiliaze_amac_task(amacTask, context, pkts, current_packet);
                current_packet++;
                if (current_packet == num_pkts) {
                    // for the remaining tasks, if not done, run to completion
                    for (int i = 0; i < context->num_interleaved_threads; i++) {
                        current_task = i;
                        amacTask = &context->amacTaskTable.amacTask[current_task];
                        amacMessage = &amacTask->amacMessage;
                        while (amacTask->done == false) {
                            actor_id = amacMessage->event;
                            entryEvent = context->actorTable.actor[actor_id].entry_event;
                            handle_entry_event(context, amacMessage, actor_id, entryEvent);
                            // run the actor
                            context->actorTable.actor[actor_id].run(amacMessage);
                            if (amacMessage->event == 255) {
                                amacTask->done = true;
                            }
                        }
                    }
                }
            }
            // switch to the next task
            context->amacTaskTable.current_task =
                    (context->amacTaskTable.current_task + 1) % context->num_interleaved_threads;
        }

    }
    // execute the action in the actor table
    DEBUG_PRINT("worker_fsm_amac_thread end\n");
}


#endif //NFLAMBDA_RUNTIME_WORKER_AMAC_THREAD_H
