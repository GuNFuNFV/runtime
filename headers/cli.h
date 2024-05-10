/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2018 Intel Corporation
 */

#ifndef CLI
#define CLI

#include <stddef.h>
#include <unistd.h>
#include "Runtime_state.h"
#include "custom_hash.h"
#include "nf/fsm_amac_nf_lib.h"

struct command_and_handler{
    char* command;
    // function pointer
    // return is char*
    // first parameter is struct worker_amac_context**
    // second parameter is char*
    // third parameter is char*
    // fourth parameter is size_t
    char* (*handler)(struct worker_amac_context*, char **, char*, size_t);
};

void cli_process(char *in, char *out, size_t out_size, int fd_client);

int cli_script_process(const char *file_name,
					   size_t msg_in_len_max,
					   size_t msg_out_len_max);



#endif /* CLI */
