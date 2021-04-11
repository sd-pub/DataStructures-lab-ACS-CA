#include <stdio.h>
#include <stdlib.h>

#include "MatrixGraph.h"
#include "utils.h"

/**
 * Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 * memorie pentru matricea de adiacenta a grafului.
 */
matrix_graph_t*
mg_create(int nodes)
{
	matrix_graph_t *mg = malloc(sizeof(*mg));
	DIE(NULL == mg, "malloc failed");

	mg->matrix = malloc(nodes * sizeof(*mg->matrix));
	DIE(NULL == mg->matrix, "malloc failed");

	for (int i = 0; i < nodes; i++) {
		mg->matrix[i] = calloc(nodes, sizeof(mg->matrix[i]));
		DIE(NULL == mg->matrix[i], "malloc failed");
		
	}

	mg->nodes = nodes;

	return mg;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void
mg_add_edge(matrix_graph_t* graph, int src, int dest)
{
	if (!graph || !graph->matrix)
		return;
	else if (src < 0 || src > graph->nodes)
		return;
	else if (dest < 0 || dest > graph->nodes)
		return;
	
	graph->matrix[src][dest] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int
mg_has_edge(matrix_graph_t* graph, int src, int dest)
{
	if (!graph)
		return 0;
	else if (src < 0 || src > graph->nodes)
		return 0;
	else if (dest < 0 || dest > graph->nodes)
		return 0;

	return graph->matrix[src][dest];
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void
mg_remove_edge(matrix_graph_t* graph, int src, int dest)
{
	if (!graph || !graph->matrix)
		return;
	else if (src < 0 || src > graph->nodes)
		return;
	else if (dest < 0 || dest > graph->nodes)
		return;
	
	graph->matrix[src][dest] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void
mg_free(matrix_graph_t* graph)
{
	for (int i =  0; i < graph->nodes; i++)
		free(graph->matrix[i]);
	free(graph->matrix);
	free(graph);
}