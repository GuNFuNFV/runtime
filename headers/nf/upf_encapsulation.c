
#include "upf_encapsulation.h"
#include "tiny_json.h"



ACTOR_CONTROL_STATE_INIT(upf_encapsulation_init) {
    struct upf_encapsulator_state *encapsulatorState = (struct upf_encapsulator_state *) rte_malloc(NULL,
                                                                                                    sizeof(struct upf_encapsulator_state),
                                                                                                    0);

    _jsonStaticPool_t spool = {.pool = {.init = poolInit, .alloc = poolAlloc}};
    // parse the config
    json_t const *json = json_createWithPool(config, &spool.pool);
    // check whether contain packet
    json_t const *packet = json_getProperty(json, "packet");
    assert(packet != 0);
    encapsulatorState->packet = (EVENT)json_getInteger(packet);
    return encapsulatorState;
}