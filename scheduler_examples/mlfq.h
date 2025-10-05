#ifndef MLFQ_H
#define MLFQ_H

#include "queue.h"
#include <stdint.h>

void mlfq_scheduler(uint32_t current_time_ms, queue_t *command_q, queue_t *rq, pcb_t **cpu_task);

#endif
