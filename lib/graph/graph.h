#ifndef GRAPH_H
#define GRAPH_H

#include "./../list/list.h"

typedef struct graph
{
    float** adj_mat;
    int size;
    float* d;
    float* pi;
    float* v;
} Graph;

Graph *graph_create(int size);
void graph_destroy(Graph *graph);
void graph_add_edge(Graph *graph, int node1, int node2, float weight);
float dijkstra_recursiv(Graph* graph, int node1, int node2);
float graph_dijkstra(Graph *graph, int node1, int node2);

#endif