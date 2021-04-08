#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"

typedef struct
{
	queue_t *f_q;
	queue_t *s_q;
} new_stack_t;

void swap_queues(queue_t **f_q, queue_t **s_q)
{
	queue_t *temp = *f_q;
	*f_q = *s_q;
	*s_q = temp;
}

void push_stack(queue_t *f_q, queue_t *s_q, void *new_data)
{
	q_enqueue(s_q, new_data);

	while (!q_is_empty(f_q)) {
		q_enqueue(s_q, q_front(f_q));
		q_dequeue(f_q);
	}

	swap_queues(&f_q, &s_q);
}

void pop_stack(queue_t *f_q, queue_t *s_q, int * elem)
{
	while(f_q->size > 1) {
		q_enqueue(s_q, q_front(f_q));
		q_dequeue(f_q);
	}

	*elem = *(int *)q_front(f_q);
	q_dequeue(f_q);
	swap_queues(&f_q, &s_q);
}

int main(void)
{
	queue_t *q1, *q2;
	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int elem;

	q1 = q_create(sizeof(int), 5);
	q2 = q_create(sizeof(int), 5);

	// push effective
	push_stack(q1, q2, &numbers[5]);
	printf("%d", *(int *)q2->buff[q2->read_idx]);
	q_dequeue(q1);

	// pop effective
	q_enqueue(q1, &numbers[6]);
	pop_stack(q1, q2, &elem);
	fprintf(stdout, "%d\n", elem);

	q_free(q1);
	q_free(q2);
	return 0;
}