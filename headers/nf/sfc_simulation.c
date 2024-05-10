

#include "sfc_simulation.h"
#include "json_helper.h"

ACTOR_CONTROL_STATE_INIT(sfc_simulation_init){
    struct SFC_Simulation_ControlState *context = (struct SFC_Simulation_ControlState *) malloc(sizeof(struct SFC_Simulation_ControlState));
//    int sfc_length;
//    int data_packing;
//    EVENT packet;
//    EVENT first_action;
//    EVENT second_action;
//    EVENT third_action;
//    EVENT fourth_action;
//    EVENT fifth_action;
//    EVENT sixth_action;
    GET_INTEGER(config, context, sfc_length);
    GET_INTEGER(config, context, datapacking);
    GET_INTEGER(config, context, packet);
    GET_INTEGER(config, context, first_action);
    GET_INTEGER(config, context, second_action);
    GET_INTEGER(config, context, third_action);
    GET_INTEGER(config, context, fourth_action);
    GET_INTEGER(config, context, fifth_action);
    GET_INTEGER(config, context, sixth_action);
    return context;

}


