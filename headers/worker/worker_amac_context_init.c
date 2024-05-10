#include "worker_amac.h"
#include "tiny_json.h"


typedef struct {
    json_t mem[256];
    unsigned int nextFree;
    jsonPool_t pool;
} jsonStaticPool_t;

//static json_t *poolInit(jsonPool_t *pool) {
//    jsonStaticPool_t *spool = json_containerOf(pool, jsonStaticPool_t, pool);
//    spool->nextFree = 1;
//    return &spool->mem[0];
//}
//
//static json_t *poolAlloc(jsonPool_t *pool) {
//    jsonStaticPool_t *spool = json_containerOf(pool, jsonStaticPool_t, pool);
//    if (spool->nextFree >= sizeof spool->mem / sizeof spool->mem[0]) return 0;
//    return &spool->mem[spool->nextFree++];
//}
//

AMAC_WORKER_INIT(init_worker_amac_context) {
    // config is formatted as "option1$value1$option2$value2$option3$value3..."
    // split the config string by $
    char *config = tokens[0];
    DEBUG_PRINT("%s\n", config);
    jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }

    // struct config_option *config_option[] = {
    //        {"worker_core_id", "int", offsetof(struct worker_amac_context, core_id)},
    //        {"worker_queue_id", "int", offsetof(struct worker_amac_context, queue_id)},
    //        {"worker_port_id", "int", offsetof(struct worker_amac_context, port_id)},
    //        {"initial_actor", "int", offsetof(struct worker_amac_context, initial_actor)},
    //        {"worker_num_interleaved", "int", offsetof(struct worker_amac_context, num_interleaved_threads)},
    //        {"worker_tx_mode", "bool", offsetof(struct worker_amac_context, tx_mode)},
    //};

    // parse worker_core_id
    json_t const *json_worker_core_id = json_getProperty(json, "worker_core_id");
    if (json_worker_core_id == NULL) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }
    pStructworkerAmacContext->core_id = json_getInteger(json_worker_core_id);

    // parse worker_queue_id
    json_t const *json_worker_queue_id = json_getProperty(json, "worker_queue_id");
    if (json_worker_queue_id == NULL) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }
    pStructworkerAmacContext->queue_id = json_getInteger(json_worker_queue_id);

    // parse worker_port_id
    json_t const *json_worker_rx_port = json_getProperty(json, "worker_rx_port");
    if (json_worker_rx_port == NULL) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }

    pStructworkerAmacContext->rx_port_id = json_getInteger(json_worker_rx_port);

    // parse worker_port_id
    json_t const *json_worker_tx_port = json_getProperty(json, "worker_tx_port");
    if (json_worker_tx_port == NULL) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }

    pStructworkerAmacContext->tx_port_id = json_getInteger(json_worker_tx_port);


    // parse initial_actor
    json_t const *json_initial_actor = json_getProperty(json, "initial_actor");
    if (json_initial_actor == NULL) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }
    pStructworkerAmacContext->initial_actor = json_getInteger(json_initial_actor);
    if (pStructworkerAmacContext->initial_actor < 0 || pStructworkerAmacContext->initial_actor > 2) {
        snprintf(out, out_size, "worker_amac_context: invalid initial actor: %d\n",
                 pStructworkerAmacContext->initial_actor);
        DEBUG_PRINT("%s", out);
        exit(1);
    }

    // parse worker_num_interleaved
    json_t const *json_worker_num_interleaved = json_getProperty(json, "worker_num_interleaved");
    if (json_worker_num_interleaved == NULL) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }
    pStructworkerAmacContext->num_interleaved_threads = json_getInteger(json_worker_num_interleaved);
    if (pStructworkerAmacContext->num_interleaved_threads < 0 ||
        pStructworkerAmacContext->num_interleaved_threads > 128) {
        snprintf(out, out_size, "worker_amac_context: invalid number of interleaved threads: %d\n",
                 pStructworkerAmacContext->num_interleaved_threads);
        DEBUG_PRINT("%s", out);
        exit(1);
    }

    // parse worker_tx_mode
    json_t const *json_worker_tx_mode = json_getProperty(json, "worker_tx_mode");
    if (json_worker_tx_mode == NULL) {
        snprintf(out, out_size, "worker_amac_context: failed to parse config: %s\n", config);
        DEBUG_PRINT("%s", out);
        exit(1);
    }
    pStructworkerAmacContext->tx_mode = (bool) json_getInteger(json_worker_tx_mode);

    json_t const *destination_instance = json_getProperty(json, "worker_destination_instance");
    if (destination_instance == NULL) {
        DEBUG_PRINT("%s", out);
    } else {
        pStructworkerAmacContext->worker_destination_instance = json_getInteger(destination_instance);
    }

    snprintf(out, out_size,
             "worker_amac_context: core_id=%d, queue_id=%d, rx_port_id=%d, initial_actor=%d, num_interleaved_threads=%d, tx_mode=%d\n",
             pStructworkerAmacContext->core_id, pStructworkerAmacContext->queue_id,
             pStructworkerAmacContext->rx_port_id, pStructworkerAmacContext->initial_actor,
             pStructworkerAmacContext->num_interleaved_threads, pStructworkerAmacContext->tx_mode);

    pStructworkerAmacContext->running = false;


    // create mbuf pool for the worker fsm
    char pool_name[100];
    sprintf(pool_name, "worker_fsm_%d_mbuf_pool", pStructworkerAmacContext->core_id);
    // socket is 0 because the nic is on socket 0
    if (pStructworkerAmacContext->mbuf_pool != NULL) {
        rte_mempool_free(pStructworkerAmacContext->mbuf_pool);
    }
    pStructworkerAmacContext->mbuf_pool = rte_pktmbuf_pool_create(pool_name, 512, 32, 0, RTE_MBUF_DEFAULT_BUF_SIZE, 0);
    if (pStructworkerAmacContext->mbuf_pool == NULL) {
        printf("Error: cannot allocate memory for mbuf_pool");
        exit(1);
    }


    // create tx buffer for the worker fsm
    char tx_buffer_name[100];
    sprintf(tx_buffer_name, "worker_fsm_%d_tx_buffer", pStructworkerAmacContext->core_id);
    if (pStructworkerAmacContext->tx_buffer != NULL) {
        rte_free(pStructworkerAmacContext->tx_buffer);
    }
    pStructworkerAmacContext->tx_buffer = rte_zmalloc(tx_buffer_name, RTE_ETH_TX_BUFFER_SIZE(8), 0);
    if (pStructworkerAmacContext->tx_buffer == NULL) {
        printf("Error: cannot allocate memory for tx_buffer");
        exit(1);
    }
    rte_eth_tx_buffer_init(pStructworkerAmacContext->tx_buffer, 8);

    pStructworkerAmacContext->amacTaskTable.num_task = pStructworkerAmacContext->num_interleaved_threads;
    pStructworkerAmacContext->running = false;
}