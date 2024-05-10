#ifndef NFLR_CIPHERING_SIMULATION_CONTROL_H
#define NFLR_CIPHERING_SIMULATION_CONTROL_H

#include "worker_amac_nf_path.h"
#include "rte_ether.h"

struct Ciphering_Simulation_ControlState {
    int probability;
    EVENT packet;
};


#endif
