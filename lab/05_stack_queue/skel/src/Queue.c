#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *queue;
	queue = malloc(sizeof(*queue));
	DIE(NULL == queue, "malloc failed");

	queue->buff = malloc(max_size * sizeof(*queue->buff));
	DIE(NULL == queue->buff, "malloc failed");

	queue->data_size = data_size;
	queue->max_size = max_size;
	queue->write_idx = 0;
	queue->read_idx = 0;
	queue->size = 0;

	return queue;
}

unsigned int
q_get_size(queue_t *q)
{
	if (!q || !q->buff)
		return 0;

	return q->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	if (q_get_size(q))
		return 0;
	
	return 1;
}

void *
q_front(queue_t *q)
{
	if (!q->size)
		return NULL;

	return q->buff[q->read_idx];
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	if (!q->size || !q)
		return false;
	
	free(q->buff[q->read_idx]);
	q->read_idx = (q->read_idx + 1) % q->max_size;
	q->size--;

	return true;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	if (!q || q->max_size == q->size)
		return false;

	q->buff[q->write_idx] = malloc(q->data_size);
	memcpy(q->buff[q->write_idx], new_data, q->data_size);
	q->write_idx = (q->write_idx + 1) % q->max_size;
	q->size++;

	return true;
}

void
q_clear(queue_t *q)
{
	for (uint i = q->read_idx; i != q->write_idx; i = (i + 1) % q->max_size) {
		free(q->buff[q->read_idx]);
		q->read_idx = (q->read_idx + 1) % q->max_size;
		q->size--;
	}

}

void
q_free(queue_t *q)
{
	q_clear(q);
	free(q->buff);
	free(q);
}
