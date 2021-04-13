#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "utils.h"

list_graph_t*
lg_create(int nodes)
{
	list_graph_t *graph;
	graph = malloc(sizeof(*graph));
	DIE(NULL == graph, "malloc failed");

	graph->neighbours = malloc(nodes * sizeof(graph->neighbours));
	DIE(NULL == graph->neighbours, "malloc failed");

	for (int i = 0; i < nodes; i++)
		graph->neighbours[i] = ll_create(sizeof(int));

	graph->nodes = nodes;

	return graph;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	if (!graph)
		return;
	else if (src < 0 || src > graph->nodes)
		return;
	else if (dest < 0 || dest > graph->nodes)
		return;

	ll_add_nth_node(graph->neighbours[src], 0, &dest);
}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	ll_node_t *current;

	if (!graph || !graph->neighbours)
		return 0;
	else if (src < 0 || src > graph->nodes)
		return 0;
	else if (dest < 0 || dest > graph->nodes)
		return 0;
	
	current = ((linked_list_t *)graph->neighbours[src])->head;

	while (current) {
		if (*(int *)current->data == dest)
			return 1;
		current = current->next;
	}

	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	if (!graph || !graph->neighbours)
		return NULL;
	
	return graph->neighbours[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	ll_node_t *current;
	int i = -1;
	if (!graph || !graph->neighbours)
		return;
	else if (src < 0 || src > graph->nodes)
		return;
	else if (dest < 0 || dest > graph->nodes)
		return;
	
	current = ((linked_list_t *)graph->neighbours[src])->head;
	while (current) {
		i++;
		if (*(int *)current->data == dest)
			break;
		current = current->next;
	}

	ll_node_t *removed = ll_remove_nth_node(graph->neighbours[src], i);
	free(removed->data);
	free(removed);
}

void
lg_free(list_graph_t* graph)
{
	if (!graph || !graph->neighbours)
		return;

	for (int i = 0; i < graph->nodes; i++) {
		linked_list_t *neighbours = (linked_list_t *)graph->neighbours[i];
		ll_free(&neighbours);
	}

	free(graph->neighbours);
	free(graph);
}