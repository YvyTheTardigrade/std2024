#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack *stack_create(){
    Stack* new_stack = malloc(sizeof(Stack));
    new_stack->first = NULL;
    new_stack->size = 0;
    return new_stack;
}


int stack_size(Stack *stack){
    return stack->size;

}
void stack_push(Stack *stack, void *data){
    StackNode* new_node = malloc(sizeof(StackNode));
    new_node->data = data;
    new_node->next = stack->first;

    stack->first = new_node;
    stack->size ++;

    return;

}
void *stack_pop(Stack *stack){
    if(stack->size == 0 ){
        printf("impossible to pop into an empty stack !\n");
        return NULL;
    }
    void* data = stack->first->data;
    StackNode* new_first = stack->first->next;
    free(stack->first);
    stack->first = new_first;
    (stack->size)-- ;
    return data;
}
void stack_destroy(Stack *stack){
    int len = stack->size;
    StackNode* to_kill = stack->first;
    StackNode* backup_next = to_kill;

    for(int i = 0; i < len - 1; i++){
        backup_next = to_kill->next;
        free(to_kill);
        to_kill = backup_next;
    }

    free(stack);
    
    return;

}