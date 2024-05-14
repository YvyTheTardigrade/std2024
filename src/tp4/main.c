#include <stdio.h>

#include "./../../lib/graph/graph.h"

int main()
{
    Graph* graph = graph_create(8);
    graph_add_edge(graph, 0, 1, 9);
    graph_add_edge(graph, 0, 5, 14);
    graph_add_edge(graph, 0, 6, 15);
    graph_add_edge(graph, 1, 2, 23);
    graph_add_edge(graph, 5, 2, 18);
    graph_add_edge(graph, 5, 4, 30);
    graph_add_edge(graph, 5, 6, 5);
    graph_add_edge(graph, 6, 7, 44);
    graph_add_edge(graph, 6, 4, 20);
    graph_add_edge(graph, 4, 7, 16);
    // ignore 5->4 car sinon cycle
    graph_add_edge(graph, 2, 7, 19); 
    graph_add_edge(graph, 2, 4, 2);
    graph_add_edge(graph, 3, 7, 6);
    graph_add_edge(graph, 3, 2, 6);

    float shortest_path = graph_dijkstra(graph, 0, 7);
    printf("shortest path length : %f\n", shortest_path);
    printf("done\n");
    graph_destroy(graph);
    /*
    
|-->------------3-----<--
|       ______/ |        |
|      /        A        |
|     V         |        |
|     4-----<---0--->----1
|      \____    |        |
|           A   V        V
|             \ |        |
|----<----------2-----<--

    */

    return 0;
}
