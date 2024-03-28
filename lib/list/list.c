#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// TODO: Implement

List *list_create(){
    List* new_list = malloc(sizeof(List));
    new_list->FirstNode = NULL;
    new_list->LastNode = NULL;
    new_list->size = 0;
    return new_list;
}

int list_size(List *list){
    return list->size;
}

void *list_get(List *list, int index){
    // |---------------|---|
    // ---------|-|
    int len = list->size;
    if((index > len) || (index < 0)){
        printf("the given index %d is unreachable\n", index);
        return NULL;
    }
    if((len - index) < (len/2)){
        // on par de la droite car plus proche de la droite
        ListNode* get_ptr = list->LastNode;
        for(int i = 0; i<len-index-1; i++){
            get_ptr = get_ptr->previous;
        }
        return get_ptr->data;

    }else{
        ListNode* get_ptr = list->FirstNode;
        for(int i = 0; i<index; i++){
            get_ptr = get_ptr->next;
        }
        return get_ptr->data;
    }
}

int list_contains(List *list, void *data){
    ListNode* to_test_ptr = list->FirstNode;
    int len = list->size;
    for(int i = 0; i < len; i++){
        if(to_test_ptr->data == data){
            return 1;
        }else{
            to_test_ptr = to_test_ptr->next;
        }
    }

    return 0;
}

void list_append(List *list, void *data){
    ListNode* node2append = malloc(sizeof(ListNode));

    node2append->data = data;
    node2append->previous = list->LastNode;
    node2append->next = NULL;


    if(list->size == 0){
        list->FirstNode = node2append;
        list->LastNode = node2append;
    }else{
        list->LastNode->next = node2append;
        list->LastNode = node2append;
    }
    
    
    list->size ++;
    return;

}

void list_insert(List *list, int index, void *data){
    int len = list->size;

    // tester si l'indice est correct
    if((index > len) || (index < 0)){
        printf("the given index %d is unreachable\n", index);
        return;
    }

    ListNode* new_node = malloc(sizeof(ListNode));
    new_node->data = data;
   
    if(index == len ){
        list_append(list, data);
        return;
    
    }else if(index == 0){

        new_node->previous = NULL; 
        new_node->next = list->FirstNode;
        list->FirstNode->previous = new_node; //pas de risque de firstnode null car  sinon ca veux dire que la chaine est vide 
                                             //et donc on insert à 0 = len => on est donc passé dans la 1ere possibilité
        list->FirstNode = new_node;
    
    }else{ 
        if((len - index - 1) < (len/2)){

            // on par de la droite car plus proche de la droite
            ListNode* next_ptr = list->LastNode;
            for(int i = 0; i<len-index-1; i++){
                next_ptr = next_ptr->previous;
            }
            // faire l'insertion a previous
            new_node->next = next_ptr;
            new_node->previous = next_ptr->previous;
            next_ptr->previous->next = new_node;
            next_ptr->previous = new_node;
            

        }else{

            ListNode* previous_ptr = list->FirstNode;
            for(int i = 0; i< index - 1; i++){ // index -1 pour s'arrêter un avant
                previous_ptr = previous_ptr->next;
            }
            //ajouter a next
            new_node->previous = previous_ptr;
            new_node->next = previous_ptr->next;
            previous_ptr->next->previous = new_node;
            previous_ptr->next = new_node;
            

        }
    }

    list->size ++;
    return;
}

int list_indexOf(List *list, void *data){
    ListNode* to_find_ptr = list->FirstNode;
    int len = list->size;
    for(int i = 0; i < len; i++){
        if(to_find_ptr->data == data){
            return i;
        }else{
            to_find_ptr = to_find_ptr->next;
        }
    }
    return -1;
    
}

void list_delete(List *list, int index){
    int len = list->size;

    // tester si l'indice est correct
    if((index >= len) || (index < 0)){
        printf("the given index %d is unreachable\n", index);
        return;
    }

    ListNode* to_kill = NULL;

    if(index == len-1){
        to_kill = list->LastNode;
        list->LastNode = to_kill->previous;
        if(to_kill->previous != NULL){
            to_kill->previous->next = NULL;
        }else{
            list->FirstNode = NULL;
        }
        

        free(to_kill);

        (list->size)--;
        return;

    }else if(index == 0){
        to_kill = list->FirstNode;
        list->FirstNode = to_kill->next;
        to_kill->next->previous = NULL;

        free(to_kill);

        (list->size)--;
        return;

    }

    if((len - index - 1) < (len/2)){
        // on par de la droite car plus proche de la droite
        to_kill= list->LastNode;

        for(int i = 0; i<len-index-1; i++){
            to_kill = to_kill->previous;
        }

    }else{

        to_kill = list->FirstNode;
        for(int i = 0; i < index; i++){ 
            to_kill = to_kill->next;
        }

    }

    to_kill->previous->next = to_kill->next;
    to_kill->next->previous = to_kill->previous;

    free(to_kill);

    (list->size)--;
    return;
    
}

void list_destroy(List *list){
    int len = list->size;
    for(int i = len - 1 ; i > -1 ; i--){
        list_delete(list, i);
    }
    free(list);
}
