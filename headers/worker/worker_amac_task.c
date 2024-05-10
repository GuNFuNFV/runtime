#include "worker_amac_task.h"
#include "rte_malloc.h"
struct amac_task_table* amac_task_table_init(int num_task) {
    struct amac_task_table *amacTaskTable = rte_malloc(NULL, sizeof(struct amac_task_table), 0);
    amacTaskTable->num_task = num_task;
    amacTaskTable->current_task = 0;
    return amacTaskTable;
}
