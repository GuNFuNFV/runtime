
#ifndef NFLAMBDA_RUNTIME_WORKER_AMAC_NFLOW_H
#define NFLAMBDA_RUNTIME_WORKER_AMAC_NFLOW_H

//obviously better ways to do this
// but for the sake of time remaining
#include "stdint.h"

typedef uint16_t NFLOW_OFFSET;
extern NFLOW_OFFSET nflowOffset[100]; // used by action actor to get the local_offset of the nflow
extern NFLOW_OFFSET generic_variable;

struct nflow_variable_setup{
    char name[100];
    int *value;
};
#endif //NFLAMBDA_RUNTIME_WORKER_AMAC_NFLOW_H
