#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "./../list/list.h"
#include "./../queue/queue.h"

#define NULL_ASSERT(ptr, name, returned_value) if(ptr == NULL){\
		printf("the pointer %s is null\n", name);\
		return returned_value;\
}


Graph *graph_create(int size){
    Graph* graph = calloc(1, sizeof(Graph));
    float** mat_rows = calloc(size, sizeof(float*));
    NULL_ASSERT(graph, "to the graph", NULL);
    NULL_ASSERT(mat_rows, "to the rows", NULL);
    for(int i = 0; i < size; i++){
        mat_rows[i] = calloc(size, sizeof(float));
        NULL_ASSERT(graph, "to a particular row", NULL);
    }
    graph->adj_mat = mat_rows;
    graph->size = size;
    float* d = calloc(size, sizeof(float));
    float* pi = calloc(size, sizeof(float));
    float* v = calloc(size, sizeof(float));
    NULL_ASSERT(d, "to d", NULL);
    NULL_ASSERT(pi, "to pi", NULL);
    NULL_ASSERT(v, "to v", NULL);
    graph->d = d;
    graph->pi = pi;
    graph->v = v;

    return graph;

}

void graph_destroy(Graph *graph){

    for(int i = 0; i < graph->size; i++){
        free((graph->adj_mat)[i]) ;
    }
    free(graph->adj_mat);
    free(graph->d);
    free(graph->pi);
    free(graph->v);
    free(graph);

}

void graph_add_edge(Graph *graph, int node1, int node2, float weight){
    NULL_ASSERT(graph, "to the graph", );
    if(graph->adj_mat[node1][node2] != 0){
        printf("a link already exists !\n");
        return;
    }
    if (node2 > graph->size || node1 > graph->size || node2 < 0 || node1 < 0 ){
        printf("incorrect node index !\n");
        return;
    }

    graph->adj_mat[node1][node2] = weight;

    //graph->adj_mat[node2][node1] = weight;
    return;
}

float graph_dijkstra(Graph *graph, int node1, int node2){
    return dijkstra_recursiv(graph, node1, node2);  
}

float dijkstra_recursiv(Graph* graph, int node1, int node2){
    if(node1 == node2){
        printf("target found\n");
        return 0;
    }

    int childrens = 0;
    float selected_result = 0;//initialiser la valeur avec une quelconque du tableau , sera remplacé a chaque iter si on trouve plus petit
    int no_path_nb = 0;
    int at_least_1_path = 0;
    for(int i = 0; i < graph->size; i++){
        if(graph->adj_mat[node1][i]){
            float path = dijkstra_recursiv(graph, i, node2);
            if(path == -1){// on ignore et incrémentons le nb de 'no path'
                no_path_nb ++;
                childrens ++;
            }else if(at_least_1_path){ // on vérifie qu'on peut comparer (séléctionner) à un optimum précédent
                float result = path  + graph->adj_mat[node1][i]; 
                childrens ++;
                if(result < selected_result){selected_result = result;}
            }else{// on crée une première valeur de ref
                float result = path  + graph->adj_mat[node1][i]; 
                childrens ++;
                at_least_1_path = 1;
                selected_result = result;
                //printf("check the else!\n");
            }
        }
    }

    if((! childrens )|| (childrens == no_path_nb)){
        return -1;
    }
    return selected_result;
    
}