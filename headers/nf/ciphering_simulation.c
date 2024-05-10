#include "ciphering_simulation.h"
#include "json_helper.h"

ACTOR_CONTROL_STATE_INIT(ciphering_simulation_init) {
    struct Ciphering_Simulation_ControlState *context = (struct Ciphering_Simulation_ControlState *) malloc(
            sizeof(struct Ciphering_Simulation_ControlState));
    GET_INTEGER(config, context, packet);
    GET_INTEGER(config, context, probability);
    return context;
}
