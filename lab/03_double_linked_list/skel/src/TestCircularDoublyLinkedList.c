#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.h"

#define MAX_STRING_SIZE 64

int main() {
	doubly_linked_list_t *doublyLinkedList, *secondlist, *sumlist, *mergedlist;
	int is_int = 0;
	int is_string = 0;
	int is_sum = 0;
	int is_merge = 0;

	while(1) {
		char command[16], added_elem[64], *end_ptr;
		long nr, pos, value;
		scanf("%s", command);
		
		if (strcmp(command, "create_str") == 0){
			doublyLinkedList = dll_create(MAX_STRING_SIZE);
			is_string = 1;
		} else if (strcmp(command, "create_int") == 0){
			doublyLinkedList = dll_create(sizeof(int));
			is_int = 1;
		} else if (strcmp(command, "add") == 0){
			scanf("%ld", &pos);
			scanf("%s", added_elem);
			nr = strtol(added_elem, &end_ptr, 10);
		
			if (nr != 0)
				dll_add_nth_node(doublyLinkedList, pos, &nr);
			else
				dll_add_nth_node(doublyLinkedList, pos, end_ptr);
		
		} else if (strcmp(command, "remove") == 0){
			scanf("%ld", &pos);
			dll_node_t *removed = dll_remove_nth_node(doublyLinkedList, pos);

			free(removed->data);
			free(removed);
		} else if (strcmp(command, "print") == 0){
			if (is_int == 1)
				dll_print_int_list(doublyLinkedList);

			if (is_string == 1)
				dll_print_string_list(doublyLinkedList);
		} else if (strcmp(command, "print_left") == 0) {
			dll_print_ints_left_circular(doublyLinkedList->head);
		} else if (strcmp(command, "print_right") == 0) {
			dll_print_ints_right_circular(doublyLinkedList->head);
		} else if (strcmp(command, "unique") == 0) {
			doublyLinkedList = dll_remove_duplicates(doublyLinkedList);
		} else if (strcmp(command, "reverse") == 0) {
			doublyLinkedList->head = dll_reverse(doublyLinkedList->head);
		} else if (strcmp(command, "sum") == 0) {
			sumlist = dll_sum_of_lists(doublyLinkedList, secondlist);
			dll_print_int_list(sumlist);

			is_sum = 1;
		} else if (strcmp(command, "merge") == 0) {
			mergedlist = dll_merge_sorted_lists(doublyLinkedList, secondlist);
			dll_print_int_list(mergedlist);

			is_merge = 1;
		} else if (strcmp(command, "create_sec") == 0) {
			secondlist = dll_create(sizeof(int));
			is_int = 1;
		} else if (strcmp(command, "sec_add") == 0){
			scanf("%ld", &pos);
			scanf("%s", added_elem);
			nr = strtol(added_elem, &end_ptr, 10);
		
			if (nr != 0)
				dll_add_nth_node(secondlist, pos, &nr);
			else
				dll_add_nth_node(secondlist, pos, end_ptr);	
		} else if (strcmp(command, "sec_print") == 0) {
			if (is_int == 1)
				dll_print_int_list(secondlist);

		} else if (strcmp(command, "less_than") == 0) {
			scanf("%ld", &value);
			doublyLinkedList->head = dll_less_than_value(doublyLinkedList, value);		
		} else if (strcmp(command, "add_middle") == 0){
			scanf("%s", added_elem);
			nr = strtol(added_elem, &end_ptr, 10);
		
			if (nr != 0)
				dll_add_middle_node(doublyLinkedList, &nr);
			else
				dll_add_middle_node(doublyLinkedList, end_ptr);	
		} else if (strcmp(command, "remove_middle") == 0) {
			dll_node_t *removed_middle;
			
			removed_middle = dll_remove_middle_node(doublyLinkedList);

			free(removed_middle->data);
			free(removed_middle);
		} else if (strcmp(command, "funky") == 0) {
			doublyLinkedList->head = dll_add_sum_of_pairs(doublyLinkedList);		
		} else if (strcmp(command, "palindrome") == 0) {
			dll_check_if_palindrome(doublyLinkedList);	
		} else if (strcmp(command, "sum_of_nums") == 0) {
			sumlist = dll_add_sum_of_two_nums(doublyLinkedList, secondlist);
			dll_print_int_list(sumlist);

			is_sum = 1;
		} else if (strcmp(command, "free") == 0) {
			dll_free(&doublyLinkedList);
			if (is_sum == 1) {
				dll_free(&secondlist);
				dll_free(&sumlist);
			} else if (is_merge == 1) {
				dll_free(&secondlist);
				dll_free(&mergedlist);
			}
			break;
		}
	}
	return 0;
}
