#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdbool.h>

#include <rte_common.h>
#include <rte_launch.h>
#include <rte_timer.h>
#include "Runtime_state.h"
#include "cli.h"
#include "conn.h"
#include "tiny_json.h"


struct Runtime_state *c;

static const char welcome[] = "hello";

static const char prompt[] = "";
struct conn *conn;
static struct app_params {
    struct conn_params conn;
    char *script_name;
} app = {.conn = {.welcome = welcome, .prompt = prompt, .addr = "0.0.0.0", .port = 8093, .buf_size = 1024 *
                                                                                                     1024, .msg_in_len_max = 2048 * 100, .msg_out_len_max =
1024 * 1024, .msg_handle = cli_process,}, .script_name = NULL,};

static void signal_handler(int signum) {
    printf("Signal %d received, preparing to exit...\n", signum);
    fflush(stdout);
    conn_free(conn);
    close(conn->fd_server);
    close(conn->fd_client_group);
    exit(0);
}

void print() {
    printf("hello");
}

struct forward_configuration {
    // source mac
    uint8_t src_mac[6];
};

int main(int argc, char *argv[]) {

    int status;
    // Error: Connectivity initialization failed
    // interrupt signal handler
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGABRT, signal_handler);
    init_EAL(argc, argv);
    runtime_init(c);
    /* Connectivity */
    conn = conn_init(&app.conn);
    if (conn == NULL) {
        printf("Error: Connectivity initialization failed (%d)\n", status);
        return status;
    }
    // current timestamp
    uint64_t current_time = rte_rdtsc();
    uint64_t last_time = current_time;
    // how many cycles per second
    uint64_t cycles_per_second = rte_get_timer_hz();
    long previous_pps[RTE_MAX_LCORE];
    for (int i = 0; i < RTE_MAX_LCORE; i++) {
        previous_pps[i] = 0;
    }
    while (!(c->cp_quit)) {
        // current timestamp
        current_time = rte_rdtsc();
        if (current_time - last_time > cycles_per_second) {
            for (int i = 0; i < 24; i++) {
                long pps = (c->worker_amac_context_list[i].total_packet - previous_pps[i]);
                printf("%ld ", pps);
                previous_pps[i] = c->worker_amac_context_list[i].total_packet;
            }
            printf("\n");
            fflush(stdout);
            last_time = current_time;
        }
        conn_poll_for_conn(conn);
        conn_poll_for_msg(conn);
    }

    conn_free(conn);
    rte_eal_mp_wait_lcore();
    return 1;
}
