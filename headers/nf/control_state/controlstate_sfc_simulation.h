#ifndef NFLR_SFC_SIMULATION_H
#define NFLR_SFC_SIMULATION_H

#include "worker_amac_nf_path.h"
#include "rte_ether.h"

struct SFC_Simulation_ControlState {
    int sfc_length;
    int datapacking;
    EVENT packet;
    EVENT first_action;
    EVENT second_action;
    EVENT third_action;
    EVENT fourth_action;
    EVENT fifth_action;
    EVENT sixth_action;
};


#endif
