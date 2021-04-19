#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
static void
dfs_connected_comps(list_graph_t *lg, int node, int *visited, 
					linked_list_t *component)
{
	stack_t *stack = st_create(sizeof(int));
	// component = ll_create(sizeof(int));

	st_push(stack, &node);

	while (!st_is_empty(stack)) {
		int s = *(int *)st_peek(stack);
		st_pop(stack);
		ll_add_nth_node(component, 0, &s);
		if (!visited[s]) {
			// printf("%d ", s);
			visited[s] = 1;
		}

		ll_node_t *current = lg_get_neighbours(lg, s)->head;
		
		while (current) {
			int next = *(int *)current->data;
			if (!visited[next])
				st_push(stack, &next);

			current = current->next;
		}
	}

	ll_print_int(component);
	printf("\n");
	st_free(stack);
}

static linked_list_t **
connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	int pos = -1;
	DIE(!comps, "malloc comps failed");
	*num_comp = 0;
	
	if (!lg || !lg->neighbors)
		return NULL;
	
	for (int i = 0; i != lg->nodes; ++i)
		comps[i] = ll_create(sizeof(int));
	
	for (int i = 0; i < lg->nodes; i++) {
		if (!visited[i]) {
			++pos;
			dfs_connected_comps(lg, i, visited, comps[pos]);
			*num_comp = *num_comp + 1;
		}
	}

	return comps;
}

static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));
	int visited_count = 0;
	queue_t *q = q_create(sizeof(int), MAX_NODES);
	
	for (int i = 0; i < lg->nodes; i++) {
		ll_node_t *current = lg_get_neighbours(lg, i)->head;
		while (current) {
			int neighbour = *(int *)current->data;
			visited[neighbour]++;
			current = current->next;
		}
	}

	for (int i = 0; i < lg->nodes; i++)
		if (!visited[i])
			q_enqueue(q, &i);

	while (!q_is_empty(q)) {
		int node = *(int *)q_front(q);
		q_dequeue(q);
		ll_add_nth_node(sorted, 0, &node);

		ll_node_t *current = lg_get_neighbours(lg, node)->head;
		while (current) {
			int next = *(int *)current->data;
			visited[next]--;
			if (!visited[next])
				q_enqueue(q, &next);
			current = current->next;
		}
		visited_count++;
	}

	q_free(q);
	return sorted;
}

static void
min_path(list_graph_t *lg, int start, int *dist)
{
	queue_t *q = q_create(sizeof(int), MAX_NODES);
	int visited[MAX_NODES] = {0};

	visited[start] = 1;
	dist[start] = 0;
	q_enqueue(q, &start);

	while (!q_is_empty(q)) {
		int s = *(int *)q_front(q);
		q_dequeue(q);

		ll_node_t *current = lg_get_neighbours(lg, s)->head;
		while (current) {
			int next = *(int *)current->data;
			if (!visited[next]) {
				visited[next] = 1;
				dist[next] = dist[s] + 1;
				q_enqueue(q, &next);
			}
			current = current->next;
		}
	}

	q_free(q);
}

static int
check_bipartite(list_graph_t *lg, int *color)
{
	queue_t *q = q_create(sizeof(int), MAX_NODES);
	int source = 0;
	color[source] = 2;
	q_enqueue(q, &source);

	while (!q_is_empty(q)) {
		int node = *(int *)q_front(q);
		q_dequeue(q);

		ll_node_t *current = lg_get_neighbours(lg, node)->head;
		while (current) {
			int next = *(int *)current->data;
			if (color[next] == 0) {
				color[next] = (color[node] == 2) ? 1 : 2;
				q_enqueue(q, &next);
			} else if (color[node] == color[next]) {
				return 0;
			}
			current = current->next;
		}
	}
	
	q_free(q);
	return 1;
}

static void
test_connected_comp(void)
{
	unsigned int num_comps = 0, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("UNDIRECTED graph for the connected components problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("Found %d connected components:\n", num_comps);
	for (i = 0; i != num_comps; ++i)
		ll_print_int(comps[i]);

	for (int i = 0; i < lg->nodes; i++)
		ll_free(&comps[i]);

	printf("\n");

	free(comps);
	lg_free(lg);
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

static void
test_min_dist(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the minimum distance problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (i = 0; i != nodes; ++i)
		dist[i] = INF;

	min_path(lg, 0, dist);

	printf("Minimum distances to node 0:\n");
	for (i = 0; i != nodes; ++i)
		printf("%u: %d\n", i, dist[i]);
	printf("\n");

	lg_free(lg);
}

static void
test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	
	if (check_bipartite(lg, color)) {
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	} else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

int
main(void)
{
	// /* Ex 1 */
	test_connected_comp();

	/* Ex 2 */
	test_topo_sort();

	// /* Ex 3 */
	test_min_dist();

	// /* Ex 4 */
	test_bipartite();

	return 0;
}
