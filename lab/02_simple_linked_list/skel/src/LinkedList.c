#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

typedef unsigned int uint;

/* create a node with a given data and it's size */
static ll_node_t *create_node(const void *new_data, uint data_size)
{
	ll_node_t *node;

	node = malloc(sizeof(*node));
	DIE(NULL == node, "malloc failed");

	node->data = malloc(data_size);
	DIE(NULL == node->data, "malloc failed");

	memcpy(node->data, new_data, data_size);

	return node;
}

/* get the node from a given position */
static ll_node_t *get_nth_node(long n, linked_list_t *list)
{
	ll_node_t *node;
	int i;

	node = list->head;
	
	for (i = 0; i < n; i++)
		node = node->next;
	
	return node;
}

/* create a list of a specified data_size */
linked_list_t*
ll_create(uint data_size)
{
	linked_list_t *list;
	
	list = malloc (sizeof(*list));
	DIE(NULL == list, "malloc failed");

	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;

	return list;
}

/* add a node on the nth position of the list given as a parameter */
void
ll_add_nth_node(linked_list_t* list, long n, const void* new_data)
{
	ll_node_t *new_node, *prev_node;

	if (n < 0 || !list) {
		fprintf(stderr, "Can't add the node\n");
		return;
	}

	if (n < 0 && !list->size) {
		fprintf(stdout, "There are zero nodes in the list\n");
		free(list);
		return;
	}
	if (n == 0) {
		n = min_int(n, list->size);
	} else if (n >= list-> size) {
		n = min_int(n, list->size);
	}

	new_node = create_node(new_data, list->data_size);

	if (!n || !list->size) {
		new_node->next = list->head;
		list->head = new_node;
	} else {
		prev_node = get_nth_node(n - 1, list);
		if (!prev_node) {
			fprintf(stderr, "Couldn't get the node\n");
			return;
		}

		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}

	list->size++;
}

/* delete a node from the nth position of the list given as a parameter */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, long n)
{
	ll_node_t *prev_node, *removed;

	if (!list || !list->size) {
		fprintf(stderr, "Can't remove the node\n");
		return NULL;
	}

	if (n < 0) {
		fprintf(stdout, "There are zero nodes in the list\n");
		free(list);
		return NULL;
	}
	
	n = min_int(n, list->size - 1);

	if (!n) {
		removed = list->head;
		list->head = list->head->next;
	} else {
		prev_node = get_nth_node(n - 1, list);
		removed = prev_node->next;
		prev_node->next = prev_node->next->next;
	}

	list->size--;

	return removed;
}

/* get the size of a list */
uint
ll_get_size(linked_list_t* list)
{
	return list->size;
}

/* free the memory allocated from a list */
void
ll_free(linked_list_t** pp_list)
{
	ll_node_t *node;

	if (!pp_list || !*pp_list)
		return;
	
	while((*pp_list)->size) {
		node = ll_remove_nth_node(*pp_list, 0);

		free(node->data);
		free(node);
	}
	
	free(*pp_list);
	*pp_list = NULL;
}

/* print a list that contains int datas */
void
ll_print_int(ll_node_t *list)
{
	ll_node_t *curr;

	if (list == NULL) {
		return;
	}

	curr = list;
	
	while (curr != NULL) {
		printf("%d ", *(int *)curr->data);
		curr = curr->next;
	}

	printf("\n");
}

/* print a list that contains string datas */
void
ll_print_string(ll_node_t *list)
{
	ll_node_t *curr;

	if (list == NULL) {
		return;
	}

	curr = list;
	
	while (curr != NULL) {
		printf("%s ", (char *)curr->data);
		curr = curr->next;
	}

	printf("\n");
}

/* reverse a given list and it apparently doesnt work,
but still seems legit */
void 
ll_reverse_full_list(linked_list_t* list)
{
	uint i = 0;

	while (i != list->size - 1) {
		ll_node_t *last = get_nth_node(list->size, list);

		ll_add_nth_node(list, 0, last->data);
		last = ll_remove_nth_node(list, list->size);
		
		free(last->data);
		free(last);
		
		i++;
	}
}

/* 311CAa problem | reverse the list to a given node, 
in this case to the head of the list */
void
ll_reverse(ll_node_t **node)
{
	ll_node_t *prev = NULL;
	ll_node_t *next = NULL;
	ll_node_t *current = *node;

	while (current != NULL) {
		next = current->next;

		current->next = prev;

		prev = current;
		current = next;
	}

	*node = prev;
}

/* merge sorted lists */
linked_list_t
*ll_merge_sorted_lists(linked_list_t *first_list, linked_list_t *second_list)
{
	linked_list_t *full_list = ll_create(first_list->data_size);
	ll_node_t *curr_first, *curr_second;
	full_list->data_size = first_list->data_size;
	
	curr_first = first_list->head;
	curr_second = second_list->head;
 
	while (curr_first && curr_second) {
		if (first_list->data_size == sizeof(int)) {
			if (*(int *)curr_first->data < *(int *)curr_second->data) {
				ll_add_nth_node(full_list, 0, curr_first->data);
				curr_first = curr_first->next;
			} else {
				ll_add_nth_node(full_list, 0, curr_second->data);
				curr_second = curr_second->next;
			}
		} else { 
			if (strcmp((char *)curr_first->data, 
						(char *)curr_second->data) < 0) {
				ll_add_nth_node(full_list, 0, curr_first->data);
				curr_first = curr_first->next;

			} else {
				ll_add_nth_node(full_list, 0, curr_second->data);
				curr_second = curr_second->next;

			}
		}
	}

	while (curr_first) {
		ll_add_nth_node(full_list, 0, curr_first->data);
		curr_first = curr_first->next;
	}

	while (curr_second) {
		ll_add_nth_node(full_list, 0, curr_second->data);
		curr_second = curr_second->next;
	}

	ll_reverse(&full_list->head);

	return full_list;
}

/* function used to verify what list to print */
void verify_c_print(linked_list_t *secondList, linked_list_t *fullList, int is_int, int is_string, int is_merged)
{
	if (is_int == 1)
		ll_print_int(secondList->head);
		
	if (is_string == 1)
		ll_print_string(secondList->head);

	if (is_merged == 1) {
		if (is_int == 1)
			ll_print_int(fullList->head);
		
		if (is_string == 1)
			ll_print_string(fullList->head);
	}
}

/* function to free all linked lists */
void ll_free_all(linked_list_t **linkedList, linked_list_t **secondList, 
				 linked_list_t **fullList, int is_sec, int is_merged, 
				 int is_split)
{
	if (is_split == 0) 
		ll_free(linkedList);
	else
		return;

	if (is_sec == 1)
		ll_free(secondList);
	
	if (is_merged == 1)
		ll_free(fullList);
	
}

/* 312CAb problem | add a node to the middle of the list */
void
ll_add_middle_node(linked_list_t *list, const void *new_data)
{
	ll_node_t *new_node, *prev_node;

	long n;
	if (!list) {
		fprintf(stderr, "There is no list\n");
		return;
	}

	n = list->size / 2;

	new_node = create_node(new_data, list->data_size);

	if (!n) {
		new_node->next = list->head;
		list->head = new_node;
	} else {
		prev_node = get_nth_node(n - 1, list);
	
		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}

	list->size++;
}

/* 312CAa problem | remove the node from the middle of the list */
ll_node_t
*ll_remove_middle_node(linked_list_t *list)
{
	long n; 

	if (!list || !list->size)
		return NULL;
	
	n = (list->size  - 1) / 2;

	return ll_remove_nth_node(list, n);
}

/* remove a given node */
void ll_free_node(ll_node_t *head)
{
	ll_node_t *rem;

	
	while (NULL != head) {
		rem = head;
		head = head->next;
		free(rem->data);
		free(rem);

	}

}

/* 313CAa problem | split a list into two lists alternating of
the position of every node */
void
ll_split_list(linked_list_t *list)
{
	ll_node_t *even = NULL;
	ll_node_t *odd = NULL;

	ll_node_t *current = list->head;

	
	while (current != NULL) {
		ll_move_node(&even, &current);

		if (current != NULL)
			ll_move_node(&odd, &current);

	}

	ll_reverse(&even);
	ll_reverse(&odd);

	/* made this here so i shouldnt have to make more functions */
	if (list->data_size == sizeof(int)) {
		ll_print_int(even);
		ll_print_int(odd);

	} else {
		ll_print_string(even);
		ll_print_string(odd);	

	}

	ll_free_node(even);
	ll_free_node(odd);
	free(list);
}

/* move the node from a source to a destination */
static void ll_move_node(ll_node_t **destination, ll_node_t **source)
{
	if (*source == NULL)
		return;

	ll_node_t *new_node = *source;
	*source = (*source)->next;
	new_node->next = *destination;
	*destination = new_node;
}

/* 313CAb problem | alternate two lists into one */
ll_node_t
*ll_alternate_lists(linked_list_t *list, linked_list_t *secondlist)
{
	ll_node_t *first = list->head;
	ll_node_t *second = secondlist->head;
	ll_node_t *alternated = NULL;


	while (first && second) {
		ll_move_node(&alternated, &first);
		
		ll_move_node(&alternated, &second);
	}

	ll_reverse(&alternated);

	return alternated;
}

/* copy a list into another, it works but not properly, the old list points to
NULL after i copy it, so i guess i need some help */
linked_list_t
*ll_copy_list(linked_list_t *list)
{
	linked_list_t *copy_list;
	
	copy_list = ll_create(list->data_size);
	
	while (list->head) {
		ll_add_nth_node(copy_list, 0, list->head->data);
		list->head = list->head->next;
	}


	return copy_list;
}

/* 315CAb problem | check if a list contains a palindrome */
void
ll_list_of_palindrome(linked_list_t *list)
{
	linked_list_t *copy_list;
	int cnt = 0;

	copy_list = ll_copy_list(list);

	ll_reverse(&copy_list->head);

	ll_print_string(list->head);
	ll_print_string(copy_list->head);

	// while (list->head && copy_list->head) {
	// 	if ((char *)list->head->data == (char *)copy_list->head->data)
	// 		cnt++;
		
	// 	list->head = list->head->next;
	// 	copy_list->head = copy_list->head->next;
	// }

	ll_print_string(list->head);
	ll_print_string(copy_list->head);

	if ((uint) cnt == list->size)
		fprintf(stdout, "the list is a palindrome");
	else
		fprintf(stdout, "the list is not a palindrome");

	ll_free(&list);
	ll_free(&copy_list);
}
