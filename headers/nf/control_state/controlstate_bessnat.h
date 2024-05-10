//
// Created by ziyan on 8/30/23.
//

#ifndef NFLR_CONTROLSTATE_BESSNAT_H
#define NFLR_CONTROLSTATE_BESSNAT_H

#include "worker_amac_nf_path.h"
#include "rte_ether.h"

struct NATControlState {
    struct rte_hash *nat_table;
    rte_be32_t *destination_ip_list;
    EVENT packet;
};


#endif //NFLR_CONTROLSTATE_BESSNAT_H
