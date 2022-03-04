#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct {
	int a_x;
	int a_y;
	int rad;
} circle_t;

static int check_intersect(circle_t *circles, int i, int j)
{
	int distance;

	distance = (circles[j].a_x - circles[i].a_x) * (circles[j].a_x - circles[i].a_x) +
					(circles[j].a_y - circles[i].a_y) * (circles[j].a_y - circles[i].a_y);

	return distance <= (circles[i].rad + circles[j].rad) * (circles[i].rad + circles[j].rad);
}

int main()
{
	int n, i, j;
	int cnt;
	circle_t *circles;
	fscanf(stdin, "%d", &n);

	cnt = 0;

	circles = malloc (n * sizeof(*circles));
	DIE(NULL == circles, "malloc failed");

	for (i = 0; i < n; ++i) {
		fscanf(stdin, "%d%d%d", &circles[i].a_x, &circles[i].a_y, &circles[i].rad);
	}


	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++)
			cnt = cnt + check_intersect(circles, i, j);
	}

	printf("%d\n", cnt);

	free(circles);
	return 0;
}
