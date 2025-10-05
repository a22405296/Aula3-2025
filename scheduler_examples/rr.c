#include "rr.h"
#include "msg.h"
#include <unistd.h>
#include <stdlib.h>

#define RR_SLICE_MS 500

// Round Robin Scheduler
void rr_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task) {
    if (*cpu_task == NULL) {
        *cpu_task = dequeue_pcb(rq);
        if (*cpu_task) {
            (*cpu_task)->slice_start_ms = current_time_ms;
        }
    }

    if (*cpu_task) {
        (*cpu_task)->ellapsed_time_ms += TICKS_MS;

        if ((*cpu_task)->ellapsed_time_ms >= (*cpu_task)->time_ms) {
            msg_t msg = {
                .pid = (*cpu_task)->pid,
                .request = PROCESS_REQUEST_DONE,
                .time_ms = current_time_ms
            };
            write((*cpu_task)->sockfd, &msg, sizeof(msg_t));
            free(*cpu_task);
            *cpu_task = NULL;
            return;
        }

        uint32_t used = current_time_ms - (*cpu_task)->slice_start_ms + TICKS_MS;
        if (used >= RR_SLICE_MS) {
            pcb_t *preempted = *cpu_task;
            preempted->slice_start_ms = 0;
            enqueue_pcb(rq, preempted);
            *cpu_task = NULL;
        }
    }
}
