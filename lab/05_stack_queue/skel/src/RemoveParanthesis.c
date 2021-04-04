#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"

typedef unsigned int uint;

#define MAX_STRING_SIZE 256

int main(void)
{
	char string[MAX_STRING_SIZE];
	int err = 0;

	stack_t *stack = st_create(sizeof(char));
	fscanf(stdin, "%s", string);

	for (uint i = 0; i < strlen(string); i++) {
		if (string[i] == '(' || string[i] == '{' || string[i] == '[') {
			st_push(stack, &string[i]);
		} else if (st_is_empty(stack)) {
			err = 1;
			break;
		} else {
			if ((string[i] == ')' && *(char *)st_peek(stack) != '(') ||
				(string[i] == '}' && *(char *)st_peek(stack) != '{') ||
				(string[i] == ']' && *(char *)st_peek(stack) != '[') ) {
				err = 1;
				break;
			}
			st_pop(stack);
		}
	}

	if (!err && !st_is_empty(stack))
		printf("The string has the paranthesis closed wrong\n");
	else if (!err)
		printf("The string has the paranthesis closed well\n");
	else 
		printf("The string has the paranthesis closed wrong\n");
	
	st_free(stack);

	return 0;
}
