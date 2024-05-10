/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2018 Intel Corporation
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <rte_common.h>
#include <rte_cycles.h>
#include <rte_ethdev.h>
#include <rte_hash.h>
#include "rte_jhash.h"
#include "rte_ether.h"
//#include <papi.h>

#include "cli.h"

#include "parser.h"
#include "worker/worker_amac.h"


#ifndef CMD_MAX_TOKENS
#define CMD_MAX_TOKENS 2048
#endif


#define MSG_CMD_UNKNOWN "Unknown command \"%s\".\n"

#define MSG_ARG_TOO_MANY "Too many arguments for command \"%s\".\n"


extern struct Runtime_state *c;

static int is_comment(char *in) {
    if ((strlen(in) && index("!#%;", in[0])) || (strncmp(in, "//", 2) == 0) || (strncmp(in, "--", 2) == 0))
        return 1;

    return 0;
}

struct command_and_handler worker_fsm_amac_commandAndHandler[] = {{"init",                            init_worker_amac_context},
                                                                  {"control_state_init",              control_state_init},
                                                                  {"worker_actor_table_init",         worker_actor_table_init},
                                                                  {"actor_control_state_association", actor_control_state_association},
                                                                  {"run",                             worker_fsm_amac_run},
                                                                  {"worker_fsm_amac_total_packet",    worker_fsm_amac_total_packet},
                                                                  {"configure_control_state",         control_state_configure},
                                                                  {"actor_datablock_association",     actor_datablock_association},
                                                                  {"init_datablock",                  init_datablock},
                                                                  {"worker_actor_entry_event",        worker_actor_entry_event}

};

void worker_fsm_amac_command(char **tokens, char *out, size_t out_size) {
    char *command = tokens[1];
    int worker_amac_id = atoi(tokens[2]);
    struct worker_amac_context *ctx = &c->worker_amac_context_list[worker_amac_id];
    char **configuration = &tokens[3];
    int worker_fsm_amac_commandAndHandler_offset;
    for (worker_fsm_amac_commandAndHandler_offset = 0; worker_fsm_amac_commandAndHandler_offset <
                                                       sizeof(worker_fsm_amac_commandAndHandler) /
                                                       sizeof(worker_fsm_amac_commandAndHandler[0]); worker_fsm_amac_commandAndHandler_offset++) {
        if (strcmp(command, worker_fsm_amac_commandAndHandler[worker_fsm_amac_commandAndHandler_offset].command) == 0) {
            worker_fsm_amac_commandAndHandler[worker_fsm_amac_commandAndHandler_offset].handler(ctx, configuration, out,
                                                                                                out_size);
            return;
        }
    }
    if (strcmp(command, "port_init") == 0) {
        DEBUG_PRINT("port_init\n");
        // get available port
        uint8_t port_id = 0;
        c->portParameter = rte_malloc(NULL, sizeof(struct port_parameter), 0);

        uint8_t nb_ports = rte_eth_dev_count_avail();
        if (nb_ports == 0) {
            DEBUG_PRINT("No Ethernet ports - bye\n");
            exit(1);
        }
        for (port_id = 0; port_id < nb_ports; port_id++) {
            c->queue_num = atoi(tokens[2]);
            c->nb_txd = 128; // descriptors per queue
            c->nb_rxd = 128; // descriptors per queue
            c->num_mbufs = 131072/128- 1;
            c->max_pkt_burst = 128;
            c->mbuf_cache_size = 128;
            struct port_parameter portParameter = {.nb_rxd = c->nb_rxd, .nb_txd = c->nb_txd, .port = port_id, .n_queue = 0, .num_mbufs = c->num_mbufs, .mbuf_cache_size = c->mbuf_cache_size};
            *(c->portParameter) = portParameter;
            char name[32];
            snprintf(name, sizeof(name), "MBUF_POOL_%d", port_id);
            c->portParameter->mempool = rte_pktmbuf_pool_create(name, c->portParameter->num_mbufs,
                                                                c->portParameter->mbuf_cache_size, 0,
                                                                RTE_MBUF_DEFAULT_BUF_SIZE, rte_eth_dev_socket_id(port_id));
            if (c->portParameter->mempool != NULL) {
                DEBUG_PRINT("mempool created\n");
            }
            c->portParameter->port = port_id;
            c->portParameter->n_queue = c->queue_num;
            port_init(c->portParameter);
        }


        DEBUG_PRINT("port_init done\n");
        snprintf(out, out_size, "port_init done\n");
        return;
    }
    DEBUG_PRINT("command %s not found\n", command);
    snprintf(out, out_size, "command %s not found\n", command);
    return;
}


void cli_process(char *in, char *out, size_t out_size, int fd_clientf) {
    char *tokens[CMD_MAX_TOKENS];
    uint32_t n_tokens = RTE_DIM(tokens);
    int status;
    uint64_t current_time;

    if (is_comment(in))
        return;

    status = parse_tokenize_string(in, tokens, &n_tokens);
    if (status) {
        snprintf(out, out_size, MSG_ARG_TOO_MANY, "");
        return;
    }

    if (n_tokens == 0)
        return;

    if (strcmp(tokens[0], "worker_fsm_amac") == 0) {
        return worker_fsm_amac_command(&tokens, out, out_size);
    }
    if (strcmp(tokens[0], "exit") == 0) {
        c->cp_quit = true;
        DEBUG_PRINT("exit done\n");
        snprintf(out, out_size, "exit done!\n");
        return;
    }
    snprintf(out, out_size, MSG_CMD_UNKNOWN);
}