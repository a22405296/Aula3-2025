#include "mlfq.h"
#include "msg.h"
#include <unistd.h>
#include <stdlib.h>

#define MLFQ_LEVELS 3
#define MLFQ_SLICE_MS 500

static queue_t levels[MLFQ_LEVELS];
static int initialized = 0;

static void init_if_needed() {
    if (!initialized) {
        for (int i = 0; i < MLFQ_LEVELS; i++) {
            levels[i].head = NULL;
            levels[i].tail = NULL;
        }
        initialized = 1;
    }
}

static void drain_ready(queue_t *rq) {
    queue_elem_t *it = rq->head;
    while (it) {
        queue_elem_t *next = it->next;
        enqueue_pcb(&levels[0], it->pcb);
        free(it);
        it = next;
    }
    rq->head = rq->tail = NULL;
}

static pcb_t *pick_next(uint32_t now) {
    for (int i = 0; i < MLFQ_LEVELS; i++) {
        if (levels[i].head) {
            pcb_t *p = dequeue_pcb(&levels[i]);
            p->slice_start_ms = now;
            return p;
        }
    }
    return NULL;
}

void mlfq_scheduler(uint32_t current_time_ms, queue_t *command_q, queue_t *rq, pcb_t **cpu_task) {
    init_if_needed();
    if (rq->head) drain_ready(rq);

    if (*cpu_task == NULL) {
        *cpu_task = pick_next(current_time_ms);
    }

    if (*cpu_task) {
        (*cpu_task)->ellapsed_time_ms += TICKS_MS;

        // Burst finished
        if ((*cpu_task)->ellapsed_time_ms >= (*cpu_task)->time_ms) {
            msg_t msg = {
                .pid = (*cpu_task)->pid,
                .request = PROCESS_REQUEST_DONE,
                .time_ms = current_time_ms
            };
            write((*cpu_task)->sockfd, &msg, sizeof(msg_t));

            // Instead of freeing → requeue to command_q
            (*cpu_task)->status = TASK_COMMAND;
            (*cpu_task)->last_update_time_ms = current_time_ms;
            enqueue_pcb(command_q, *cpu_task);

            *cpu_task = NULL;
            return;
        }

        // Time slice expired
        uint32_t used = current_time_ms - (*cpu_task)->slice_start_ms + TICKS_MS;
        if (used >= MLFQ_SLICE_MS) {
            static int level_hint = 0;
            if (level_hint < MLFQ_LEVELS - 1) level_hint++;
            enqueue_pcb(&levels[level_hint], *cpu_task);
            *cpu_task = NULL;
        }
    }
}
