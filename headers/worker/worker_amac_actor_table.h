
#ifndef NFLAMBDA_RUNTIME_WORKER_AMAC_ACTOR_TABLE_H
#define NFLAMBDA_RUNTIME_WORKER_AMAC_ACTOR_TABLE_H
#include "message.h"
enum ENTRY_EVENT{
    LOAD_PERFLOW_STATE, // load the perflow state and the control state
    LOAD_CLASSIFIER_STATE, // load the classifier state and the control state
    LOAD_CONTROL_STATE, // just load the control state
    ENTRY_POINT_DO_NOTHING, // do nothing
};

enum EXIT_EVENT{
    EXIT_PREFECH_PERFLOW_STATE,
    EXIT_PREFECH_CLASSIFIER_STATE,
    // we take care of this later
    EXIT_NO_EVENT,
};

#define MAXIMUM_ACTOR 300

struct actor{
    uint8_t control_state_id; // corresponding to the index of control state table
    uint8_t datablock_id; // corresponding to the index of datablock
    uint8_t datablock_offset; // corresponding to the offset of the datablock; datablock can be shared by multiple actors;
    void*control_state;
    ACTOR_ACTION_PTR run; // function that need to run
    enum ENTRY_EVENT entry_event;
    enum EXIT_EVENT exit_event[MAXIMUM_ACTOR]; // the exit event of each actor; how to handle also depends on the next actor
};

struct worker_actor_table{
    struct actor actor[MAXIMUM_ACTOR];
    int num_actor;
};

#include "worker_amac_macro.h"



struct runtime_actor_table{
    char name[100];
    ACTOR_ACTION_PTR run; // function that need to run
};



#endif //NFLAMBDA_RUNTIME_WORKER_AMAC_ACTOR_TABLE_H
