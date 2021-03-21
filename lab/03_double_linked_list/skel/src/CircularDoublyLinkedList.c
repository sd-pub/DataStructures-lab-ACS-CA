#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

typedef unsigned int uint;

/* create a node with a given data and it's size */
static dll_node_t *create_node(const void *new_data, uint data_size)
{
	dll_node_t *node;

	node = malloc(sizeof(*node));
	DIE(NULL == node, "malloc failed");

	node->data = malloc(data_size);
	DIE(NULL == node->data, "malloc failed");

	memcpy(node->data, new_data, data_size);

	return node;
}

/* create a list of a specified data_size */
doubly_linked_list_t*
dll_create(uint data_size)
{
	doubly_linked_list_t *list;

	list = malloc(sizeof(*list));
	DIE(NULL == list, "malloc failed");

	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;

	return list; 
}

/* get the node from a given position */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, uint n)
{
	dll_node_t *node;
	uint i;

	if (!list || !list->size)
		return NULL;

	if (n < 0 && !list->size) {
		fprintf(stdout, "Cant get the nth node\n");
		return NULL;
	}

	node = list->head;
	
	n = n % list->size;

		for (i = 0; i < n; i++)
			node = node->next;

	return node;
}

/* add a node on the nth position of the list given as a parameter */
void
dll_add_nth_node(doubly_linked_list_t* list, uint n, const void* data)
{
	dll_node_t *new_node, *prev_node, *curr_node;

	if (n < 0 || !list) {
		fprintf(stderr, "Can't add the node\n");
		return;
	}

	if (n < 0 && !list->size) {
		fprintf(stdout, "There are zero nodes in the list\n");
		free(list);
		return;
	}

	if (n >= list-> size)
		n = list->size;


	new_node = create_node(data, list->data_size);

	if (!list->size) {
		new_node->next = new_node;
		new_node->prev = new_node;
		list->head = new_node;
	} else if (n == 0) {
		curr_node = dll_get_nth_node(list, n);

		new_node->next = curr_node;
		new_node->prev = curr_node->prev;
		
		curr_node->prev->next = new_node;
		curr_node->prev = new_node;

		list->head = new_node;
	} else {
		prev_node = dll_get_nth_node(list, n - 1);

		new_node->next = prev_node->next;
		prev_node->next->prev = new_node;

		prev_node->next = new_node;
		new_node->prev = prev_node;
	}

	list->size++;
}

/* delete a node from the nth position of the list given as a parameter */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, uint n)
{
	dll_node_t *removed;


	if (!list || !list->size) {
		fprintf(stderr, "Can't remove the node\n");
		return NULL;
	}

	if (n < 0) {
		fprintf(stdout, "Can't remove the node\n");
		return NULL;
	}
	
	if (n >= list->size)
		n = list->size - 1;

	if (!n) {
		removed = list->head;
		list->head = removed->next;

	} else {
		removed = dll_get_nth_node(list, n);
	}

	removed->next->prev = removed->prev;
	removed->prev->next = removed->next;

	list->size--;

	if (!list->size)
		list->head = NULL;
	
	return removed;
}

/* get the size of a list */
uint
dll_get_size(doubly_linked_list_t* list)
{
	return list->size;
}

/* free the memory allocated from a list */
void
dll_free(doubly_linked_list_t** pp_list)
{
	dll_node_t *node;

	if (!pp_list || !*pp_list)
		return;
	
	while((*pp_list)->size) {
		node = dll_remove_nth_node(*pp_list, 0);

		free(node->data);
		free(node);
	}
	
	free(*pp_list);
	*pp_list = NULL;
}

/* print a list that contains int datas */
void
dll_print_int_list(doubly_linked_list_t* list)
{
	dll_node_t *curr;

	if (list == NULL)
		return;


	curr = list->head;


	for (uint i = 0; i < list->size; i++) {
		printf("%d ", *(int *)curr->data);
		curr = curr->next;
	}

	printf("\n");
}

/* print a list that contains string datas */
void
dll_print_string_list(doubly_linked_list_t* list)
{
	dll_node_t *curr;

	if (list == NULL)
		return;

	curr = list->head;

	for (uint i = 0; i < list->size; i++) {
		printf("%s ", (char *)curr->data);
		curr = curr->next;
	}

	printf("\n");
}

/* print a list in left direction */
void
dll_print_ints_left_circular(dll_node_t* start)
{
	dll_node_t *curr;

	curr = start;

	while (curr->prev != start) {
		printf("%d ", *(int *)curr->data);
		curr = curr->prev;
		if (curr->prev == start)
			printf("%d ", *(int *)start->next->data);
	}

	printf("\n");
}

/* print a list in right direction */
void
dll_print_ints_right_circular(dll_node_t* start)
{
	dll_node_t *curr;

	curr = start;

	while (curr->next != start) {
		printf("%d ", *(int *)curr->data);
		curr = curr->next;
		if (curr->next == start)
			printf("%d ", *(int *)start->prev->data);
	}
	
	printf("\n");
}

/* 311CAa problem | remove duplicates from a list */
doubly_linked_list_t
*dll_remove_duplicates(doubly_linked_list_t *list)
{
	dll_node_t *curr, *removed, *new_next;
	curr = list->head;

	while (curr->next != list->head) {
		if (list->data_size == sizeof(int)) {
			if (*(int*)curr->data == *(int *)curr->next->data) {
				new_next = curr->next->next;
				removed = curr->next;
				free(removed->data); 
				free(removed);

				curr->next = new_next;
				new_next->prev = curr->next;
				list->size--;  
			} else {
				curr = curr->next;
			}
		} else {
			if ((char *)curr->data == (char *)curr->next->data) {
				new_next = curr->next->next;
				removed = curr->next;
				free(removed->data); 
				free(removed);

				curr->next = new_next;
				new_next->prev = curr->next;
				list->size--;  
			} else {
				curr = curr->next;
			}
		}
	}

	return list;
}

/* function to add a given node at the end of the list */
static void
dll_insert_end(dll_node_t **head, dll_node_t * new_node) 
{
	dll_node_t *last;

	if (*head == NULL) {
		new_node->next = new_node->prev = new_node;
		*head = new_node;
		return;
	}

	last = (*head)->prev;

	new_node->next = *head;
	(*head)->prev = new_node;

	new_node->prev = last;	
	last->next = new_node;
}

/* 311CAb problem | reverse the list to a given node, 
in this case to the head of the list */
dll_node_t
*dll_reverse(dll_node_t *head)
{
	if (!head)
		return NULL;
	
	dll_node_t *new_head, *last, *curr, *prev;
	
	new_head = NULL;
	last = head->prev;
	curr = last;

	while (curr->prev != last) {
		prev = curr->prev;

		dll_insert_end(&new_head, curr);
		curr = prev;
	}
	dll_insert_end(&new_head, curr);

	return new_head;
}

/* reverse a given list but you alloc new memory*/
void
dll_reverse_not_cool
(doubly_linked_list_t *list) 
{
	dll_node_t *removed, *curr;
	curr = list->head;
	uint n = list->size;

	for (uint i = 0; i < n; i++) {
		dll_add_nth_node(list, list->size - i, curr->data);

		removed = dll_remove_nth_node(list, 0);
		free(removed->data);
		free(removed);
		removed = NULL;

		curr = curr->next;
	}
	
}

/* 312CAb problem | make a new list with every node->data the 
sum of two lists data */
doubly_linked_list_t
*dll_sum_of_lists(doubly_linked_list_t *list, doubly_linked_list_t *secondlist) 
{
	doubly_linked_list_t *newlist;
	dll_node_t *curr_one, *curr_sec;
	int  sum = 0;
	uint n;
	
	if (!list || !secondlist)
		return NULL;
	
	newlist = dll_create(sizeof(int));

	if (list->size > secondlist->size)
		n = list->size;
	else
		n = secondlist->size;
	
	curr_one = list->head;
	curr_sec = secondlist->head;

	for (uint i = 0; i < n; i++) {
		if (list->size - 1 < i)
			sum = *(int *)curr_sec->data;
		else if (secondlist->size - 1 < i)
			sum = *(int *) curr_one->data;
		else
			sum = *(int *) curr_one->data + *(int *)curr_sec->data;
		
		dll_add_nth_node(newlist, 0, &sum);
		
		curr_one = curr_one->next;
		curr_sec = curr_sec->next;
	}

	dll_reverse(newlist->head);
	
	return newlist;
}

/* 313CAa problem | merge two sorted lists */
doubly_linked_list_t
*dll_merge_sorted_lists(doubly_linked_list_t *first_list, doubly_linked_list_t *second_list)
{
	doubly_linked_list_t *full_list = dll_create(first_list->data_size);
	dll_node_t *curr_first, *curr_second;
	full_list->data_size = first_list->data_size;
	
	uint n = first_list->size + second_list->size;
	uint i = 0, j = 0;

	curr_first = first_list->head;
	curr_second = second_list->head;
 
	while (i != first_list->size && j != second_list->size) {
		if (first_list->data_size == sizeof(int)) {
			if (*(int *)curr_first->data < *(int *)curr_second->data) {
				dll_add_nth_node(full_list, 0, curr_first->data);
				curr_first = curr_first->next;
				i++;
			} else {
				dll_add_nth_node(full_list, 0, curr_second->data);
				curr_second = curr_second->next;
				j++;
			}
		} else { 
			if (strcmp((char *)curr_first->data, 
						(char *)curr_second->data) < 0) {
				dll_add_nth_node(full_list, 0, curr_first->data);
				curr_first = curr_first->next;
				i++;

			} else {
				dll_add_nth_node(full_list, 0, curr_second->data);
				curr_second = curr_second->next;
				j++;

			}
		}
	}

	while (i != first_list->size) {
		dll_add_nth_node(full_list, 0, curr_first->data);
		curr_first = curr_first->next;
		i++;
	}

	while (j != second_list->size) {
		dll_add_nth_node(full_list, 0, curr_second->data);
		curr_second = curr_second->next;
		j++;
	}

	full_list->head = dll_reverse(full_list->head);

	return full_list;
}

/* function to insert a node in the first position */
static void
dll_insert_first(dll_node_t **head, dll_node_t *new_node) 
{
	dll_node_t *last;

	if (*head == NULL) {
		new_node->next = new_node->prev = new_node;
		*head = new_node;
		return;
	}

	new_node->next->prev = new_node->prev;
	new_node->prev->next = new_node->next;

	last = (*head)->prev;

	new_node->next = *head;
	new_node->prev = last;

	last->next = (*head)->prev = new_node;

	*head = new_node;
}

/* 313CAb problem | move all the datas which are smaller than 
a given value to the left of the list 
which surprsingly doesnt work and i cant get the hang of it, YET */
dll_node_t
*dll_less_than_value(doubly_linked_list_t *list, int value)
{
	dll_node_t *curr;

	if (!list->head)
		return NULL;

	curr = list->head;

	for (uint i = 0; i < list->size; i++) {
		dll_node_t *nextnode = curr->next;
		
		if (*(int *) curr->data <= value) {
			dll_insert_first(&list->head, curr);
			curr = nextnode;
		}
		
	}

	return list->head;
}

/* 314CAb problem | add a node to the middle of the list */
void
dll_add_middle_node(doubly_linked_list_t *list, const void *new_data)
{
	dll_add_nth_node(list, list->size / 2, new_data);

}

/* 315CAa problem | remove the node from the middle of the list */
dll_node_t
*dll_remove_middle_node(doubly_linked_list_t *list)
{
	long n; 

	if (!list || !list->size)
		return NULL;
	
	n = (list->size - 1) / 2;

	return dll_remove_nth_node(list, n);
}