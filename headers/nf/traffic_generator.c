

#include "traffic_generator.h"

#include "tiny_json.h"


//#include "json_helper.h"

ACTOR_CONTROL_STATE_INIT(traffic_generator_init) {
    DEBUG_PRINT("traffic_generator_state_init\n");
    DEBUG_PRINT("%s\n", config);
    struct traffic_generator_state *trafficGeneratorState = (struct traffic_generator_state *) rte_malloc(NULL,
                                                                                                          sizeof(struct traffic_generator_state),
                                                                                                          0);

    // parse config
    _jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        DEBUG_PRINT("json_createWithPool failed\n");
        return NULL;
    }

    // analysis traffic_class_num as int
    json_t const *traffic_class_num = json_getProperty(json, "traffic_class_num");
    if (!traffic_class_num) {
        DEBUG_PRINT("traffic_class_num not found\n");
        exit(1);
    }
    trafficGeneratorState->traffic_class_num = json_getInteger(traffic_class_num);
    DEBUG_PRINT("traffic_class_num: %d\n", trafficGeneratorState->traffic_class_num);

    for (int i = 0; i < trafficGeneratorState->traffic_class_num; i++) {
        char *traffic_class_name = (char *) rte_malloc(NULL, 100, 0);
        sprintf(traffic_class_name, "traffic_class#%d", i);
        json_t const *traffic_class = json_getProperty(json, traffic_class_name);
        if (!traffic_class) {
            DEBUG_PRINT("traffic_class not found\n");
            return NULL;
        }
        DEBUG_PRINT("traffic_class_name: %s\n", traffic_class_name);

        json_t const *destination_instance = json_getProperty(traffic_class, "destination_instance");
        if (!destination_instance) {
            DEBUG_PRINT("destination_instance not found\n");
            exit(1);
        }
        trafficGeneratorState->traffic_class[i].destination_instance = json_getInteger(destination_instance);
        DEBUG_PRINT("destination_instance: %d\n", trafficGeneratorState->traffic_class[i].destination_instance);

        json_t const *flow_id_lower = json_getProperty(traffic_class, "flow_id_lower");
        if (!flow_id_lower) {
            DEBUG_PRINT("flow_id_lower not found\n");
            exit(1);
        }
        trafficGeneratorState->traffic_class[i].flow_id_lower = json_getInteger(flow_id_lower);
        DEBUG_PRINT("flow_id_lower: %d\n", trafficGeneratorState->traffic_class[i].flow_id_lower);

        json_t const *flow_id_upper = json_getProperty(traffic_class, "flow_id_upper");
        if (!flow_id_upper) {
            DEBUG_PRINT("flow_id_upper not found\n");
            exit(1);
        }
        trafficGeneratorState->traffic_class[i].flow_id_upper = json_getInteger(flow_id_upper);
        DEBUG_PRINT("flow_id_upper: %d\n", trafficGeneratorState->traffic_class[i].flow_id_upper);

        json_t const *packet_size = json_getProperty(traffic_class, "packet_size");
        if (!packet_size) {
            DEBUG_PRINT("packet_size not found\n");
            exit(1);
        }
        trafficGeneratorState->traffic_class[i].packet_size = json_getInteger(packet_size);
        DEBUG_PRINT("packet_size: %d\n", trafficGeneratorState->traffic_class[i].packet_size);

        json_t const *proportion = json_getProperty(traffic_class, "proportion");
        if (!proportion) {
            DEBUG_PRINT("proportion not found\n");
            exit(1);
        }
        trafficGeneratorState->traffic_class[i].proportion = json_getReal(proportion);
        DEBUG_PRINT("proportion: %d\n", trafficGeneratorState->traffic_class[i].proportion);

        json_t const *subflow_id_lower = json_getProperty(traffic_class, "subflow_id_lower");
        if (!subflow_id_lower) {
            DEBUG_PRINT("subflow_id_lower not found\n");
            exit(1);
        }
        trafficGeneratorState->traffic_class[i].subflow_id_lower = json_getInteger(subflow_id_lower);

        json_t const *subflow_id_upper = json_getProperty(traffic_class, "subflow_id_upper");
        if (!subflow_id_upper) {
            DEBUG_PRINT("subflow_id_upper not found\n");
            exit(1);
        }
        trafficGeneratorState->traffic_class[i].subflow_id_upper = json_getInteger(subflow_id_upper);



        DEBUG_PRINT(
                "traffic_class: destination_instance: %d, flow_id_lower: %d, flow_id_upper: %d, packet_size: %d, proportion: %d, subflow_id_lower: %d, subflow_id_upper: %d\n",
                trafficGeneratorState->traffic_class[i].destination_instance,
                trafficGeneratorState->traffic_class[i].flow_id_lower,
                trafficGeneratorState->traffic_class[i].flow_id_upper,
                trafficGeneratorState->traffic_class[i].packet_size, trafficGeneratorState->traffic_class[i].proportion,
                trafficGeneratorState->traffic_class[i].subflow_id_lower,
                trafficGeneratorState->traffic_class[i].subflow_id_upper);
    }
//    json_t const *traffic_class_num = json_getProperty(json, "traffic_class_num");
//    if (!traffic_class_num) {
//        DEBUG_PRINT("traffic_class_num not found\n");
//        exit(1);
//    }
//    trafficGeneratorState->traffic_class_num = json_getInteger(traffic_class_num);


    struct worker_amac_context* p_worker_context = (struct worker_amac_context*) worker_context;

    trafficGeneratorState->port_id = p_worker_context->tx_port_id;
    trafficGeneratorState->queue_id = p_worker_context->queue_id;
    trafficGeneratorState->core_id = p_worker_context->core_id;
    trafficGeneratorState->batch_size = BATCH_SIZE;
    trafficGeneratorState->mbuf = rte_malloc(NULL, sizeof(struct rte_mbuf *) * trafficGeneratorState->batch_size, 0);
    trafficGeneratorState->worker_amac_context = p_worker_context;
    int ret = rte_pktmbuf_alloc_bulk(p_worker_context->mbuf_pool, trafficGeneratorState->mbuf,
                                     trafficGeneratorState->batch_size);

    trafficGeneratorState->total_proportion = 0;
    for (int i = 0; i < trafficGeneratorState->traffic_class_num; i++) {
        trafficGeneratorState->total_proportion += trafficGeneratorState->traffic_class[i].proportion;
    }

    int current_slot = 0;
    for (int i = 0; i < trafficGeneratorState->traffic_class_num; i++) {
        for (int j = 0; j < trafficGeneratorState->traffic_class[i].proportion; j++) {
            trafficGeneratorState->scheduling_slots[current_slot] = i;
            current_slot++;
        }
    }


    if (ret != 0) {
        DEBUG_PRINT("rte_pktmbuf_alloc_bulk failed\n");
        exit(1);
    }
    return trafficGeneratorState;
}


ACTOR_CONTROL_STATE_CONFIGURE(traffic_generator_configure) {

}