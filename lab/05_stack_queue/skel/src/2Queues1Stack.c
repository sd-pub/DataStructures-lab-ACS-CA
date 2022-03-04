#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

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

int pop_stack(queue_t *f_q, queue_t *s_q)
{
	int elem;
	while(f_q->size > 1) {
		q_enqueue(s_q, q_front(f_q));
		q_dequeue(f_q);
	}

	elem = *(int *)q_front(f_q);
	q_dequeue(f_q);
	swap_queues(&f_q, &s_q);

	return elem;
}

int main(void)
{
	new_stack_t *st;
	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int elem;

	st = malloc(sizeof(*st));
	DIE(NULL == st, "malloc failed");

	st->f_q = q_create(sizeof(int), 5);
	st->s_q = q_create(sizeof(int), 5);

	// push effective
	push_stack(st->f_q, st->s_q, &numbers[5]);
	printf("%d\n", *(int *)q_front(st->s_q));
	q_dequeue(st->f_q);

	// pop effective
	q_enqueue(st->f_q, &numbers[6]);
	elem = pop_stack(st->f_q, st->s_q);
	fprintf(stdout, "%d\n", elem);

	
	q_free(st->f_q);
	q_free(st->s_q);
	free(st);
	return 0;
}