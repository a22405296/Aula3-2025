#include "sjf.h"
#include "msg.h"
#include <unistd.h>
#include <stdlib.h>

//Shortest Job First
void sjf_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task) {
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
        }
    }

    if (*cpu_task == NULL) {
        // Pick process with smallest remaining time
        queue_elem_t *it = rq->head;
        queue_elem_t *best_prev = NULL;
        queue_elem_t *best = NULL;
        uint32_t best_remaining = 0;
        queue_elem_t *prev = NULL;

        while (it) {
            pcb_t *p = it->pcb;
            uint32_t remaining = (p->time_ms > p->ellapsed_time_ms)
                ? (p->time_ms - p->ellapsed_time_ms) : 0;
            if (!best || remaining < best_remaining) {
                best = it;
                best_prev = prev;
                best_remaining = remaining;
            }
            prev = it;
            it = it->next;
        }

        if (best) {
            if (best_prev) best_prev->next = best->next;
            else rq->head = best->next;
            if (rq->tail == best) rq->tail = best_prev;
            *cpu_task = best->pcb;
            (*cpu_task)->slice_start_ms = current_time_ms;
            free(best);
        }
    }
}
