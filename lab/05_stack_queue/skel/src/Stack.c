#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t *
st_create(unsigned int data_size)
{
	/* TODO */
	stack_t *stack;

	stack = malloc(sizeof(*stack));
	DIE(NULL == stack, "malloc failed");

	stack->list = ll_create(data_size);

	return stack;
}

unsigned int
st_get_size(stack_t *st)
{
	ll_node_t *current = st->list->head;
	int i;

	for (i = 0; current; i++)
		current = current->next;

	return i;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st)
{
	if (st_get_size(st))
		return 0;
	
	return 1;
}

void *
st_peek(stack_t *st)
{
	if (!st)
		return NULL;

	return st->list->head->data;
}

void
st_pop(stack_t *st)
{
	if (!st || !st->list)
		return;

	ll_node_t *removed = ll_remove_nth_node(st->list, 0);
	free(removed->data);
	free(removed);
}

void
st_push(stack_t *st, void *new_data)
{
	if (!st || !st->list)
		return;
	
	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st)
{
	if (!st || !st->list)
		return;

	while (st->list->size) {
		ll_node_t *removed = ll_remove_nth_node(st->list, 0);
		free(removed->data);
		free(removed);
	}

}

void
st_free(stack_t *st)
{
	if (!st)
		return;

	ll_free(&st->list);
	free(st);
}
