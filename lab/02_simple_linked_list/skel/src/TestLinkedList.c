#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 64

int
main()
{
	linked_list_t* linkedList, *secondList, *fullList;
	int is_int = 0;
	int is_string = 0;
	int is_sec = 0;
	int is_merged = 0;
	int is_split = 0;
	int is_conc = 0;
	while (1) {
		char command[16], added_elem[64], *end_ptr;
		char *sec_end_ptr, sec_added_elem[64];
		char new_data[64], *new_end_ptr;
		long nr, pos, sec_nr, sec_pos, new_nr;
		scanf("%s", command);
		if (strcmp(command, "create_str") == 0) {
			linkedList = ll_create(MAX_STRING_SIZE);

			is_string = 1;
		} else if (strcmp(command, "create_int") == 0) {
			linkedList = ll_create(sizeof(int));

			is_int = 1;
		} else if (strcmp(command, "add") == 0) {
			scanf("%ld", &pos);
			scanf("%s", added_elem);

			nr = strtol(added_elem, &end_ptr, 10);

			if (nr != 0)
				ll_add_nth_node(linkedList, pos, &nr);
			else
				ll_add_nth_node(linkedList, pos, end_ptr);
		} else if (strcmp(command, "remove") == 0) {
			scanf("%ld", &pos);

			ll_node_t *removed;
			removed = ll_remove_nth_node(linkedList, pos);

			free(removed->data);
			free(removed);
		} else if (strcmp(command, "print") == 0) {
			if (is_int == 1)
				ll_print_int(linkedList->head);

			if (is_string == 1)
				ll_print_string(linkedList->head);
		} else if (strcmp(command, "reverse") == 0) {
			ll_reverse(&linkedList->head);

		} else if (strcmp(command, "list_reverse") == 0) {
			ll_reverse_full_list(linkedList);

		} else if (strcmp(command, "combine_create") == 0) {
				if (is_int == 1)
					secondList = ll_create(MAX_STRING_SIZE);
				else
					secondList = ll_create(sizeof(int));

				is_sec = 1;
		} else if (strcmp(command, "combine_add") == 0) {
			scanf("%ld", &sec_pos);
			scanf("%s", sec_added_elem);

			sec_nr = strtol(sec_added_elem, &sec_end_ptr, 10);

			if (sec_nr != 0)
				ll_add_nth_node(secondList, sec_pos, &sec_nr);
			else
				ll_add_nth_node(secondList, sec_pos, sec_end_ptr);
		} else if (strcmp(command, "combine_print") == 0) {
			verify_c_print(secondList, fullList, is_int, is_string, is_merged);

		} else if (strcmp(command, "merge_bruh") == 0) {
			fullList = ll_merge_sorted_lists(linkedList, secondList);
			
			is_merged = 1;
		} else if (strcmp(command, "remove_middle") == 0) {
			ll_node_t *removed_middle;
			
			removed_middle = ll_remove_middle_node(linkedList);

			free(removed_middle->data);
			free(removed_middle);
		} else if (strcmp(command, "add_middle") == 0) {
			scanf("%s", new_data);

			new_nr = strtol(new_data, &new_end_ptr, 10);

			if (new_nr != 0)
				ll_add_middle_node(linkedList, &new_nr);
			else
				ll_add_middle_node(linkedList, new_end_ptr);

		} else if (strcmp(command, "split_list") == 0) {
			ll_split_list(linkedList);
			is_split = 1;
		} else if (strcmp(command, "alternate") == 0) {
			ll_node_t *alternated_list = ll_alternate_lists(linkedList, 
											secondList);
			
			ll_print_int(alternated_list);

			ll_free_node(alternated_list);
			free(linkedList);
			free(secondList);

			is_conc = 1;

		} else if (strcmp(command, "palindrome") == 0) {
			ll_list_of_palindrome(linkedList);
		} else if (strcmp(command, "free") == 0) {
			if (is_conc == 0)
				ll_free_all(&linkedList, &secondList, &fullList, is_sec, is_merged,
							is_split);
			
			break;
		}
	}
	return 0;
}
