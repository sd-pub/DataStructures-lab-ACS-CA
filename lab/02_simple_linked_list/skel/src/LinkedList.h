#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_
#include <stdbool.h>

typedef unsigned int uint;

typedef struct ll_node_t ll_node_t;
struct ll_node_t
{
    void* data;
    ll_node_t* next;
};

typedef struct linked_list_t linked_list_t;
struct linked_list_t
{
    ll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

linked_list_t*
ll_create(uint data_size);

void
ll_add_nth_node(linked_list_t* list, long n, const void* new_data);

ll_node_t*
ll_remove_nth_node(linked_list_t* list, long n);

int
ll_get_size(ll_node_t *head);

void
ll_free(linked_list_t** pp_list);

void
ll_print_int(ll_node_t* list);

void
ll_print_string(ll_node_t *list);

void 
ll_reverse_full_list(linked_list_t* list);

void 
ll_reverse(ll_node_t **node);

void verify_c_print(linked_list_t *secondList, linked_list_t *fullList, int is_int, int is_string, int is_merged);

void ll_free_all(linked_list_t **linkedList, linked_list_t **secondList, 
				 linked_list_t **fullList, int is_sec, int is_merged, 
				 int is_split);

linked_list_t
*ll_merge_sorted_lists(linked_list_t *first_list, linked_list_t *second_list);

void
ll_add_middle_node(linked_list_t *list, const void *new_data);

ll_node_t
*ll_remove_middle_node(linked_list_t *list);

void
ll_split_list(linked_list_t *list);

void ll_free_node(ll_node_t *head);

ll_node_t
*ll_alternate_lists(linked_list_t *list, linked_list_t *secondlist);

void
ll_list_of_palindrome(linked_list_t *list);

ll_node_t
*remove_nth_node_from_end(ll_node_t *head, int n);

bool
ll_is_palindrome(ll_node_t *head);

ll_node_t 
*ll_intersect_of_lists(ll_node_t *headOne, ll_node_t *headTwo);

ll_node_t
*sort_list(ll_node_t* head); 

#endif /* __LINKED_LIST_H_ */
