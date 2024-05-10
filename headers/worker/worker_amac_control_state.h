
#ifndef NFLAMBDA_RUNTIME_WORKER_AMAC_CONTROL_STATE_H
#define NFLAMBDA_RUNTIME_WORKER_AMAC_CONTROL_STATE_H
#define ACTOR_CONTROL_STATE_INIT(name) void* name(char* config, int core_id, int port_id, int queue_id, void* worker_context)
// add int core_id, int port_id, int queue_id kinda break the abstraction, but we need it for the traffic generator for optimal performance. we can change it later
typedef ACTOR_CONTROL_STATE_INIT((*ACTOR_CONTROL_STATE_INIT_PTR));
#define ACTOR_CONTROL_STATE_CONFIGURE(name) void name(void*control_state, char* config)
typedef ACTOR_CONTROL_STATE_CONFIGURE((*ACTOR_CONTROL_STATE_CONFIGURE_PTR));
struct control_state_table {
    char name[100];
    ACTOR_CONTROL_STATE_INIT_PTR init; // function that need to run
    ACTOR_CONTROL_STATE_CONFIGURE_PTR config;
    // used by the runtime for the association between the control state name and the initialization function
};

struct worker_control_state {
    void *control_state; // the state of the state in the state machine
};

struct worker_control_state_table {
    struct worker_control_state control_state[100];
    int num_control_state;
};


#endif //NFLAMBDA_RUNTIME_WORKER_AMAC_CONTROL_STATE_H
