#include "fastclick_lb.h"
#include "tiny_json.h"


static inline int power2(int a) {
    if (a == 0)
        return 1;
    else
        return 2 * power2(a - 1);
}

ACTOR_CONTROL_STATE_INIT(fastclick_lb_init) {
    struct LBControlState *pLbControlState = (struct LBControlState *) rte_malloc(NULL, sizeof(struct LBControlState),
                                                                                  0);
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
    pLbControlState->packet = json_getInteger(packet);

    int entry_num = power2(20);
    pLbControlState->destination_ip_list = (rte_be32_t *) rte_malloc(NULL, sizeof(rte_be32_t) * entry_num, 0);
    for (int i = 0; i < entry_num; i++) {
        pLbControlState->destination_ip_list[i] = (rte_be32_t) i;
    }

    return pLbControlState;
}