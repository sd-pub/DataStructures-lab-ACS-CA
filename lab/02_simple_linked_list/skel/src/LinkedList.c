#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
int
ll_get_size(ll_node_t* head)
{
	int i;
	for (i = 0; head; i++)
		head = head->next;

	return i;
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

/* 19th problem from leetcode || Remove nth node from end of list */
ll_node_t
*remove_nth_node_from_end(ll_node_t *head, int n)
{
	ll_node_t *first, *second;

	first = second = head;

	for (int i = 0; i < n; i++) {
		first = first->next;
		if (!first)
			return head->next;
	}

	while (first->next != NULL) {
		second = second->next;
		first = first->next;
	}
	ll_node_t *rem = second->next;
	second->next = second->next->next;

	free(rem->data);
	free(rem);
	
	return head;
}

/* reverse half a list and return the end point and the start point of it*/
static void
ll_reverse_half(ll_node_t *head, int n, ll_node_t **left_head_ptr, 
				ll_node_t **right_head_ptr)
{
	ll_node_t *prev = NULL;
	
	for (int i = 0; i < n / 2 && head; i++) {
		ll_node_t *temp = head->next;
		head->next = prev;
		prev = head;
		head = temp;
	}

	*left_head_ptr = prev;
	*right_head_ptr = head;
}

/* repair the list after reversing it */
static void
ll_repair_half(ll_node_t *left, ll_node_t *right)
{
	 while (left) {
		ll_node_t *temp = left->next;
		left->next = right;
		right = left;
		left = temp;
	}
}


/* 234th problem from leetcode || 315CAb || O(n) - time and O(1) - space */
bool
ll_is_palindrome(ll_node_t *head)
{
	int n = ll_get_size(head);

	ll_node_t* left_head;
	ll_node_t* right_head;
	ll_reverse_half(head, n, &left_head, &right_head);
	
	ll_node_t* left = left_head;
	ll_node_t* right = right_head;
	
	if (n % 2 == 1)
		right = right->next;

	
	while (left || right) {
		if (*(int*)left->data != *(int*)right->data) {
			ll_repair_half(left_head, right_head);
			return false;
		}

		left = left->next;
		right = right->next;
	}
	
	ll_repair_half(left_head, right_head);

	return true;  
}

/* 237th problem from leetcode || remove given node of a list */
void ll_remove_node(ll_node_t *node)
{
	ll_node_t *dummy;
	dummy = node->next;

	memcpy(node->data, dummy->data, sizeof(int));

	node->next = node->next->next;

	free(dummy);
	free(dummy->data);
}

/* 160th problem from leetcode || intersect value of two lists */
ll_node_t 
*ll_intersect_of_lists(ll_node_t *headOne, ll_node_t *headTwo)
{
	ll_node_t *ptrA = headOne;
	ll_node_t *ptrB = headTwo;

	while (ptrA != ptrB) { 
		ptrA = ptrA ? ptrA->next : headTwo;
		ptrB = ptrB ? ptrB->next : headOne;
	}

	return ptrA;
}

ll_node_t * merge(ll_node_t * l1, ll_node_t * l2)
{
	ll_node_t * dump;
	ll_node_t * cur = &dump;
	
	while (l1 != NULL && l2 != NULL) {
		if (*(int *)l1->data < *(int *)l2->data) {
			cur->next = l1;
			l1 = l1->next;
		} else {
			cur->next = l2;
			l2 = l2->next;
		}
			
		cur = cur->next;
	}
	
	if (l1 != NULL)
		cur->next = l1;
	else
		cur->next = l2;
		
	return dump->next;
}

/* 148th problem from leetcod | sort a list with merge sort implementation */
ll_node_t * sortList(ll_node_t * head) 
{
	if (head == NULL || head->next == NULL)
		return head;
	
	ll_node_t * slow = head;
	ll_node_t * fast = head->next;
	
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	
	fast = slow->next;
	slow->next = NULL;
	
	return merge(sortList(head), sortList(fast));
}


/* 141th problem from leetcode | check if there is a cycle in the list */
bool
ll_is_cycle(ll_node_t *head)
{
	ll_node_t *fast, *slow;
	fast = head;
	slow = head;
	
	while (slow && fast && fast->next) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) 
			return true;
	}
	return false;
}