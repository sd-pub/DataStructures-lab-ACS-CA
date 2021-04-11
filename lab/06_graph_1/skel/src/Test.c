#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Stack.h"
#include "Queue.h"

#define MAX_NODES 10
#define MAX_INT 11500
static int time;

void
print_matrix_graph(matrix_graph_t* mg)
{
	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++)
			fprintf(stdout, "%d ", mg->matrix[i][j]);
		
		fprintf(stdout, "\n");
	}
}

void
print_list_graph(list_graph_t* lg)
{
	for (int i = 0; i < lg->nodes; i++) {
		printf("neighbours for %d are: ", i);
		ll_print_int(lg->neighbours[i]);
	}

}

void
dfs_list_graph(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_tin)
{
	time = 0;
	stack_t *stack = st_create(sizeof(int));
	memset(visited, 0, MAX_NODES * sizeof(int));

	st_push(stack, &node);

	while (!st_is_empty(stack)) {
		int s = *(int *)st_peek(stack);
		st_pop(stack);
		if (!visited[s]) {
			t_desc[s]= time++;
			printf("%d ", s);
			visited[s] = 1;

		}

		ll_node_t *current = lg_get_neighbours(lg, s)->head;
		
		while (current) {
			int next = *(int *)current->data;
			if (!visited[next])
				st_push(stack, &next);

			current = current->next;
		}
		t_tin[s] = time++;
	}

	printf("\n");
	st_free(stack);
}

void
dfs_matrix_graph(matrix_graph_t* mg,
		 int node,
		 int* visited,
		 int* t_desc,
		 int* t_tin)
{
	if (visited[node]) 
		return;

	visited[node] = 1;
	t_desc[node] = time++;
	printf("%d ", node);
	
	for (int i = 0; i < mg->nodes; i++)
		if (mg->matrix[node][i]) {
			if (!visited[i])
				dfs_matrix_graph(mg, i, visited, t_desc, t_tin);
		}

	t_desc[node] = time++;
}

void
bfs_list_graph(list_graph_t* lg, int node, int* visited)
{
	time = 0;
	queue_t *q = q_create(sizeof(int), MAX_NODES);
	memset(visited, 0, MAX_NODES * sizeof(int));

	q_enqueue(q, &node);

	while (!q_is_empty(q)) {
		int s = *(int *)q_front(q);
		q_dequeue(q);
		if (!visited[s]) {
			printf("%d ", s);
			visited[s] = 1;

		}

		ll_node_t *current = lg_get_neighbours(lg, s)->head;
		
		while (current) {
			int next = *(int *)current->data;
			if (!visited[next])
				q_enqueue(q, &next);

			current = current->next;
		}
	}

	printf("\n");

	q_free(q);
}

void
bfs_matrix_graph(matrix_graph_t* mg, int node, int* visited)
{
	queue_t *q = q_create(sizeof(int), MAX_NODES);

	visited[node] = 1;
	q_enqueue(q, &node);

	while (!q_is_empty(q)) {
		int s = *(int *)q_front(q);
		q_dequeue(q);
		printf("%d ", s);
		

		for (int i = 0; i < mg->nodes; i++) {
			if (mg->matrix[s][i] && !visited[i]) {
				visited[i] = 1;
				q_enqueue(q, &i);
			}
		}
	}
	
	printf("\n");
	q_free(q);
}

void
floyd_warshall(matrix_graph_t* mg)
{
	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++) {
			if (mg->matrix[i][j] == 0 && i != j)
				mg->matrix[i][j] = MAX_INT;
		}
	}

	for (int k = 0; k < mg->nodes; k++) {
    	for (int i = 0; i < mg->nodes; i++) {
        	for (int j = 0; j < mg->nodes; j++) {
				if (mg->matrix[i][j] > mg->matrix[i][k] + mg->matrix[k][j])
					mg->matrix[i][j] = mg->matrix[i][k] + mg->matrix[k][j];
        	}
   		}
	}

	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++) {
			if (mg->matrix[i][j] == MAX_INT && i != j)
				mg->matrix[i][j] = 0;
		}
	}
}

int
main()
{
	int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);


	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));
	
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[0], numbers[2]);
	mg_add_edge(mg, numbers[0], numbers[3]);
	mg_add_edge(mg, numbers[2], numbers[4]);

	// print_list_graph(lg);
	// print_matrix_graph(mg);

	dfs_list_graph(lg, numbers[0], visited, t_dest, t_fin);
	bfs_list_graph(lg, numbers[0], visited);
	
	memset(visited, 0, MAX_NODES * sizeof(int));
	time = 0;
	dfs_matrix_graph(mg, numbers[0], visited, t_dest, t_fin);
	printf("\n");

	memset(visited, 0, MAX_NODES * sizeof(int));
	bfs_matrix_graph(mg, numbers[0], visited);
	
	// Matrice random de testare
	int cnt = 1;
	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++) {
			if (mg->matrix[i][j] == 1) {
				mg->matrix[i][j] = cnt;
				cnt++;
			}
		}
			
	}

	printf("Matricea inainte de FW\n");
	print_matrix_graph(mg);

	floyd_warshall(mg);
	
	printf("Matricea dupa FW\n");
	print_matrix_graph(mg);

	lg_free(lg);
	mg_free(mg);
	return 0;
}
