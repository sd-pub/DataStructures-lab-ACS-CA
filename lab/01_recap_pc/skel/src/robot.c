#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define CMAX 256
#define uc unsigned char

static uc **alloc_matrix(int rows, int columns)
{
	int i = 0, j = 0;
	uc **points;

	points = malloc(rows * sizeof(*points));
	DIE(NULL == points, "malloc failed");

	for (i = 0; i < rows; ++i) {
		points[i] = malloc(columns * sizeof(*points[i]));
		DIE(NULL == points[i], "malloc failed");
		
	}
	
	return points;  
}

static void print_matrix(int rows, int columns, uc **points) {
	int i = 0, j = 0;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			fprintf(stdout, "%u ", points[i][j]);
		}
		fprintf(stdout, "\n");
	}
}

static void free_mem(uc **points, int rows)
{
	int i = 0;

	for (i = 0; i < rows; i++)
		free(points[i]);
	free(points);
}

static int robots_way(uc **points, unsigned long length, int rows, int columns, char *commands)
{
	int i, pos_x = 0, pos_y = 0;

	for (i = 0; i < (int) length; ++i) {
		if (commands[i] == 'D') {
			if (pos_x + 1 > rows) {
				fprintf(stdout, "Robot got out of range\n");

				free_mem(points, rows);
				return -1;
			} else {
				points[pos_x][pos_y] = 0;
				++pos_x;
				points[pos_x][pos_y] = 1;

				print_matrix(rows, columns, points);
				printf("\n");
			}
		} else if (commands[i] == 'U') {
			if (pos_x - 1 < 0) {
				fprintf(stdout, "Robot got out of range\n");
				free_mem(points, rows);

				return -1;
			} else {
				points[pos_x][pos_y] = 0;
				pos_x--;
				points[pos_x][pos_y] = 1;

				print_matrix(rows, columns, points);
				printf("\n");
			}
		} else if (commands[i] == 'R') {
			if (pos_y + 1 > columns) {
				fprintf(stdout, "Robot got out of range\n");
				free_mem(points, rows);

				return -1;
			} else {
				points[pos_x][pos_y] = 0;
				pos_y++;
				points[pos_x][pos_y] = 1;

				print_matrix(rows, columns, points);
				printf("\n");
			}
		} else {
			if (pos_y - 1 < 0) {
				fprintf(stdout, "Robot got out of range\n");
				free_mem(points, rows);

				return -1;
			} else {
				points[pos_x][pos_y] = 0;
				pos_y--;
				points[pos_x][pos_y] = 1;

				print_matrix(rows, columns, points);
				printf("\n");
			}
		}
	}

	return 0;
}

int main(void)
{
	int rows, columns;
	char commands[CMAX];
	uc **points;
	unsigned long length;
	int verify, i, j;

	fscanf(stdin, "%d%d", &rows, &columns);
	fscanf(stdin, " %s", commands);

	points = alloc_matrix(rows, columns);

	for (i = 0; i < rows; i++)
		for (j = 0; j < columns; j++)
			points[i][j] = 0;
	
	points[0][0] = 1;

	length = strlen(commands);

	verify = robots_way(points, length, rows, columns, commands);

	if (verify != -1) {
		if (points[0][0] == 1)
			fprintf(stdout, "TRUE\n");
		else
			fprintf(stdout, "FALSE\n");

		free_mem(points, rows);
	}

	return 0;
}
