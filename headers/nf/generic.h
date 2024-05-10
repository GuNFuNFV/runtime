
#ifndef NFLAMBDA_RUNTIME_GENERIC_H
#define NFLAMBDA_RUNTIME_GENERIC_H

#include "fsm_amac_nf_common.h"

struct generic_state {
    int state_id;
    char state_name[100];
    int generic_level; // access mode 0 with data packing access mode 1 without data packing
    int generic_access_mode;
    int generic_access_size; // how many cache lines need to be accessed
    EVENT packet;
};

static inline void dump_binary(void *data, int size) {
    for (int i = 0; i < size; i++) {
        // print as hex
        printf("%02x ", ((uint8_t *) data)[i]);
    }
    printf("\n");
    fflush(stdout);
}

static inline void increment_binary_mode0(void *data, int size) {
    for (int i = 0; i < size; i++) {
        ((uint8_t *) data)[i]++; // with data packing
    }
}

static inline void random_function(void *data, int size){
    for (int i = 0; i < size; i++) {
        ((uint8_t *) data)[i]++; // with data packing
    }
    DEBUG_PRINT("data: %p\n", data);
}
static inline void increment_binary_mode1(void *data, int size) {
    for (int i = 0; i < size; i++) {
        (*((uint8_t *) data))++;
        // move 1 cache line
        data = (uint8_t *) ((uint8_t *) data + 64); // each memory location is 1 byte
    }
//    DEBUG_PRINT("increment_binary_mode1 done\n");
}

INLINE_ACTOR_ACTION(generic) {
//    DEBUG_PRINT("generic action\n");
    struct generic_state *genericState = (struct generic_state *) m->control_state;
    // checkout data
//    dump_binary(m->data_state, genericState->generic_access_size);
    switch (genericState->generic_access_mode) {
        case 0:
            increment_binary_mode0(m->data_state, genericState->generic_access_size);
            break;
        case 1:
            increment_binary_mode1(m->data_state, genericState->generic_access_size);
            break;
    }
    m->event = genericState->packet;
//    printf("generic action done\n");
//    fflush(stdout);
}

ACTOR_CONTROL_STATE_INIT(generic_init);

#endif //NFLAMBDA_RUNTIME_GENERIC_H
