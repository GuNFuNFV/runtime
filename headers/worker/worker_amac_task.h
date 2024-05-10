#ifndef NFLAMBDA_RUNTIME_AMAC_TASK_H
#define NFLAMBDA_RUNTIME_AMAC_TASK_H

#include "message.h"
#include "stdbool.h"
enum stage{
    PREFETCH_REFETENCE_STAGE,
    PREFETCH_DATA_STAGE,
    EXECUTE_STAGE,
};
struct nftask{
    struct message amacMessage;
    bool done;
    int datablock_id;
    uint8_t stage; // 0 for not prefetch, 1 for prefetched
};

struct amac_task_table{
    struct nftask amacTask[128];
    int num_task;
    int current_task;
    int task_done;
    int current_level;// which classifier_state datablock_id is currently running
};

struct amac_task_table* amac_task_table_init(int num_task);
#endif //NFLAMBDA_RUNTIME_AMAC_TASK_H
