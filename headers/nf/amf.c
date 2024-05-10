#include "amf.h"
#include "tiny_json.h"


ACTOR_CONTROL_STATE_INIT(amf_init) {
    DEBUG_PRINT("amf_init\n");
    DEBUG_PRINT("%s\n", config);
    struct amf_control_state *control_state = (struct amf_control_state *) rte_malloc(NULL,
                                                                                      sizeof(struct amf_control_state),
                                                                                      0);
    // parse config
    _jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        DEBUG_PRINT("json_createWithPool failed\n");
        return NULL;
    }

    EXTRACT_JSON_INT_PROPERTY(json, control_state, reserved);

//    json_t const *reserved = json_getProperty(json, "reserved");
//    if (reserved) {
//        control_state->reserved = json_getInteger(reserved);
//    }

    json_t const *unregistered = json_getProperty(json, "unregistered");
    if (unregistered) {
        control_state->unregistered = (EVENT) json_getInteger(unregistered);
    }

    json_t const *registered = json_getProperty(json, "registered");
    if (registered) {
        control_state->registered = (EVENT) json_getInteger(registered);
    }
    json_t const *context_setup = json_getProperty(json, "context_setup");
    if (context_setup) {
        control_state->context_setup = (EVENT) json_getInteger(context_setup);
    }

    json_t const *authentication = json_getProperty(json, "authentication");
    if (context_setup) {
        control_state->authentication = (EVENT) json_getInteger(authentication);
    }

    json_t const *prefetch_mode = json_getProperty(json, "prefetch_mode");
    if (prefetch_mode) {
        control_state->prefetch_mode = json_getInteger(prefetch_mode);
    }

    json_t const *packet = json_getProperty(json, "packet");
    if (packet) {
        control_state->packet = (EVENT) json_getInteger(packet);
    }

    DEBUG_PRINT("control_state->reserved: %d\n", control_state->reserved);
    DEBUG_PRINT("control_state->unregistered: %d\n", (int) control_state->unregistered);
    DEBUG_PRINT("control_state->registered: %d\n", (int) control_state->registered);
    DEBUG_PRINT("control_state->context_setup: %d\n", (int) control_state->context_setup);
    DEBUG_PRINT("control_state->authentication: %d\n", (int) control_state->authentication);
    DEBUG_PRINT("control_state->packet: %d\n", (int) control_state->packet);
    DEBUG_PRINT("control_state->prefetch_mode: %d\n", control_state->prefetch_mode);
    return control_state;
}