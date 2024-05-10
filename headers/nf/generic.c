
#include "generic.h"

#include "tiny_json.h"

struct amac_nf_init_option generic_options[] = {"state_id", "state_name", "generic_access_size", "generic_access_mode",
                                                "packet"};

ACTOR_CONTROL_STATE_INIT(generic_init) {
    DEBUG_PRINT("generic_init\n");
    DEBUG_PRINT("%s\n", config);
    struct generic_state *genericState = (struct generic_state *) rte_malloc(NULL, sizeof(struct generic_state), 0);
    // parse config
    _jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        DEBUG_PRINT("json_createWithPool failed\n");
        return NULL;
    }
    json_t const *generic_access_size = json_getProperty(json, "generic_access_size");
    if (generic_access_size) {
        genericState->generic_access_size = json_getInteger(generic_access_size);
    }
    json_t const *generic_access_mode = json_getProperty(json, "generic_access_mode");
    if (generic_access_mode) {
        genericState->generic_access_mode = json_getInteger(generic_access_mode);
    }
    json_t const *packet = json_getProperty(json, "packet");
    if (packet) {
        genericState->packet = (EVENT) json_getInteger(packet);
    }

    DEBUG_PRINT("genericState->generic_access_size: %d\n", genericState->generic_access_size);
    DEBUG_PRINT("genericState->generic_access_mode: %d\n", genericState->generic_access_mode);
    DEBUG_PRINT("genericState->packet: %d\n", (int) genericState->packet);

    return genericState;
}