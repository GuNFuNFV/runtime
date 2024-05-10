
#ifndef NFLAMBDA_RUNTIME_MULTI_LEVEL_H
#define NFLAMBDA_RUNTIME_MULTI_LEVEL_H

struct multi_level_state{
    void** state[5];
    int num_state;
    int current_level;
};


#endif //NFLAMBDA_RUNTIME_MULTI_LEVEL_H
