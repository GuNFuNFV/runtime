
#include "passthrough.h"
#include "tiny_json.h"



ACTOR_CONTROL_STATE_INIT(passthrough_init){
    DEBUG_PRINT("passthrough_init\n");

    struct passthrough_context *context = (struct passthrough_context *) malloc(sizeof(struct passthrough_context));
    _jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    json_t const *json = json_createWithPool(config, &spool.pool);
    if (!json) {
        DEBUG_PRINT("json_createWithPool failed\n");
        return NULL;
    }
    json_t const *packet = json_getProperty(json, "packet");
    if (!packet) {
        DEBUG_PRINT("json_getProperty failed\n");
        return NULL;
    }
    context->packet = json_getInteger(packet);
    DEBUG_PRINT("packet: %d\n", context->packet);
    return context;
}