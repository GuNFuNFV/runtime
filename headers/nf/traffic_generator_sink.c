

#include "traffic_generator_sink.h"
#include "json_helper.h"


ACTOR_CONTROL_STATE_INIT(traffic_generator_sink_init) {
    struct trafic_generator_sink_control_state *TGSC = rte_zmalloc("traffic_generator_sink_control_state",
                                                                   sizeof(struct trafic_generator_sink_control_state),
                                                                   0);
    GET_INTEGER(config, TGSC, packet);
    return TGSC;
}

