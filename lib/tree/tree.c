#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "./../list/list.h"
#include "./../queue/queue.h"
#include "./../stack/stack.h"

#define NULL_ASSERT(ptr, name, returned_value) if(ptr == NULL){\
		printf("the pointer %s is null\n", name);\
		return returned_value;\
}

int alloc_nb = 0;
int free_nb = 0;

Tree *tree_create(){
    Tree* tree = malloc(sizeof(Tree));
    alloc_nb ++;
    NULL_ASSERT(tree, "tree", NULL);

    tree->root = NULL;

    tree->size = 0;

    return tree;

}

TreeNode *tree_search(Tree *tree, void *data, int (*cmp)(void *, void *)){
    NULL_ASSERT(tree, "to the given tree", NULL);
    NULL_ASSERT(tree->root, "to the root", NULL);

    TreeNode* current = tree->root;
    if(current->data == data){return current;}
    while(current != NULL){
        int id_to_visit;
        int cmp_id = cmp(data, current->data);
        if( cmp_id < 0){
            id_to_visit = -2*cmp_id +1;
        }else{
            id_to_visit = 2*cmp_id;
        }
        if(current->childrens->size > id_to_visit){
            TreeNode* res = list_get(current->childrens, id_to_visit);
            NULL_ASSERT(res, "to visit", NULL);
            if(res->data == data){
                return res;
            } else {
                current = res;
            }
        }else{
            printf("data not found...\n");
            return NULL;
        }
    }
    printf("data was not found\n");
    return NULL;
    
}
void tree_destroy_recursiv(TreeNode* tree){
    NULL_ASSERT(tree, "to the given tree", );
    List* childrens = tree->childrens;
    for (int i = 0; i<childrens->size; i++){
        TreeNode* tree_2_kill = list_get(childrens, i);
        if (tree_2_kill == NULL){continue;}
        
        tree_destroy_recursiv(tree_2_kill);
        //free(tree_2_kill);
        free_nb ++;
    }
    list_destroy(childrens);
    free(tree);
    free_nb ++;
}

void tree_destroy(Tree *tree){
    /*NULL_ASSERT(tree, "to the given tree", );
    List* childrens = tree->root->childrens;
    list_destroy(tree->root->childrens);
    free(tree->root);
    tree->root = childrens->FirstNode;
    for(int i = 1; i<childrens->size; i++){
        Tree* child;
        child->root = list_get(childrens, i);
        NULL_ASSERT(child->root, "'child' tree", );
        tree_destroy(child);  
    }
    list_destroy(childrens);*/
    tree_destroy_recursiv(tree->root);
    //free(tree->root);
    free(tree);
    free_nb +=1; 

}


void tree_insert(Tree *tree, void *data, int (*cmp)(void *, void *)){
    // gérer cas d'égalité
    NULL_ASSERT(tree, "to the given tree", );
    if (tree->size == 0){
        TreeNode* new_node = calloc(1, sizeof(TreeNode));
        alloc_nb ++;
        new_node->data = data;
        new_node->childrens = list_create();
        tree->root = new_node;
        tree->size ++;
        return;
    }
    NULL_ASSERT(tree->root, "to the root", );

    TreeNode* current = tree->root;
    while(current != NULL){
        int id_to_insert;
        int cmp_id = cmp(data, current->data);
        if( cmp_id < 0){
            id_to_insert = -2*cmp_id +1;
        }else{
            id_to_insert = 2*cmp_id;
        }
        if(current->childrens->size > id_to_insert){
            TreeNode* res = list_get(current->childrens, id_to_insert);
            if(res == NULL){
                TreeNode* new_node = calloc(1, sizeof(TreeNode));
                alloc_nb ++;
                NULL_ASSERT(tree, "named 'newnode'",);
                new_node->data = data;
                new_node->childrens = list_create();
                list_set(current->childrens, new_node, id_to_insert);
                tree->size ++;
                break;
            } else {
                current = res;
            }
        }else{
            int nb2append = id_to_insert - current->childrens->size ;

            for(int i = 0; i < nb2append; i++){
                list_append(current->childrens, NULL);
            }
            
            TreeNode* new_node = calloc(1, sizeof(TreeNode));
            alloc_nb ++;
            NULL_ASSERT(tree, "named 'newnode'",);
            new_node->data = data;
            new_node->childrens = list_create();//on append un pointeur sur node qui contient en data dat2 mais l'accès à ce pointeur est nul
            list_append(current->childrens, new_node);
            tree->size ++;
            break;
        }
    }
    printf("data successfully inserted\n");
} 

List *tree_bfs(Tree *tree){
    Queue* container = queue_create();
    List* result = list_create();
    queue_enqueue(container, tree->root);
    //list_append(result, tree->root->data);
    int counter = 1;
    while(result->size < tree->size){   
        //vérifier que on saute bien les node null
        TreeNode* root = queue_dequeue(container);
        list_append(result, root->data);
        if(root->childrens->size == 0){continue;};

        for(int j = root->childrens->size-1; j > 0 ; j--){//int j = 0; j < root->childrens->size; j++
            TreeNode* child = list_get(root->childrens, j);
            if(child == NULL){continue;}
            queue_enqueue(container, child);
            
            counter ++;
        }
    
    }
    queue_destroy(container);
    return result;
}

List *tree_dfs(Tree *tree){
    Stack* container = stack_create();
    List* result = list_create();
    stack_push(container, tree->root);
    //list_append(result, tree->root->data);
    int counter = 1;
    while(result->size < tree->size){   
        // for (int i = 0; i<container->size; i++){
        TreeNode* root = stack_pop(container);
        list_append(result, root->data);
        if(root->childrens->size == 0){continue;};

        for(int j = 0; j < root->childrens->size; j++){// ou insérer a l'envers
            TreeNode* child = list_get(root->childrens, j);
            if(child == NULL){continue;}
            stack_push(container, child);
            
            counter ++;
        }
        
    }
    stack_destroy(container);
    return result;

}

void print_free_alloc_nb(void){
    printf("%d was allocated\n%d has been freed\n",alloc_nb, free_nb);
}