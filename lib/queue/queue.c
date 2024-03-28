#include "queue.h"
#include <stdlib.h>
#include <stdio.h>


Queue *queue_create(){
    void* ptr = malloc(sizeof(Queue));
    Queue* queue = NULL;
    if(ptr != NULL){
        queue = ptr; 
        queue -> FirstNode = NULL;
        queue -> LastNode = NULL;
        queue -> size = 0;
        return queue;
    }else{
        printf("l'espace mémoire n'est pas disponible");
        return NULL;
    }   
}

void queue_destroy(Queue *queue){
    QueueNode* to_kill = queue->FirstNode;
    QueueNode* backup_next = NULL;
    int len  = queue->size;

    for(int i = 0; i < len; i++){
        backup_next = to_kill->next;
        free(to_kill);
        to_kill = backup_next;
    }

    free(queue);

    return;
}

void queue_enqueue(Queue *queue, void *data){
    void* ptr = malloc(sizeof(QueueNode));
    QueueNode* newNode = NULL;
    if(ptr != NULL){
        newNode = ptr;
        newNode -> data = data;
        newNode -> next = NULL;
        if(queue->LastNode != NULL){
            queue->LastNode->next = newNode;
            queue->LastNode = newNode;
        }else{
            queue->LastNode = newNode;
            queue->FirstNode = newNode;
        }
        
        queue->size++;
        return ;
    }else{
        printf("l'espace mémoire n'est pas disponible");
        return ;
    }
    
}

void *queue_dequeue(Queue *queue){
    int len = queue->size;
    if(len == 0){
        printf("impossible to dequeue an empty queue\n");
        return NULL;
    }
    void* data = queue->FirstNode->data;
    if(len > 1){
        QueueNode* newnext = queue->FirstNode->next; 
        free(queue->FirstNode);
        queue->FirstNode = newnext; 
    }else{
        free(queue->FirstNode);
        queue->FirstNode = NULL;
        queue->LastNode = NULL;
    }
    
     
    (queue->size)-- ;
    return data;

}


int queue_size(Queue *queue){
    return queue->size;
}
