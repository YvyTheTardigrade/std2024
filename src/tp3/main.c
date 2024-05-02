#include <stdio.h>

#include "./../../lib/list/list.h"
#include "./../../lib/tree/tree.h"

int int_cmp(void *a, void *b){
    int x = (int) a;
    int y = (int) b;
    if(x < y){
        return -1;
    } else if(x > y){
        return 1;
    } else {
        return 0;
    }
}
int main(){
/*
    5
   / \ 
  1   6
   \   \
    2   7
     \   \
      3   8
       \   \
        4   9 
*/
    Tree *tree = tree_create();
    int dat1 = 1;
    int dat2 = 2;
    int dat3 = 3;
    int dat4 = 4;
    int dat5 = 5;
    int dat6 = 6;
    int dat7 = 7;
    int dat8 = 8;
    int dat9 = 9;
    
    printf("dat5 : %p,dat1 : %p,dat2 : %p,dat3 : %p,dat4 : %p,dat6 : %p,dat7 : %p,dat8 : %p,dat9 : %p\n", &dat5, &dat1, &dat2, &dat3, &dat4, &dat6, &dat7, &dat8, &dat9);

    tree_insert(tree, &dat5, &int_cmp);
    tree_insert(tree, &dat1, &int_cmp);
    tree_insert(tree, &dat2, &int_cmp);
    tree_insert(tree, &dat3, &int_cmp);
    tree_insert(tree, &dat4, &int_cmp);
    tree_insert(tree, &dat6, &int_cmp);
    tree_insert(tree, &dat7, &int_cmp);
    tree_insert(tree, &dat8, &int_cmp);
    tree_insert(tree, &dat9, &int_cmp);

    List* bfs = tree_dfs(tree);

    for (int i = 0; i<bfs->size; i++){
        int* data = list_get(bfs, i);
        printf("%d\n",*(data));
    }
    
    tree_destroy(tree);
    list_destroy(bfs);
    print_free_alloc_nb();

    Tree *tree2 = tree_create();
    
    tree_insert(tree2, (void *) 5, int_cmp);
    tree_insert(tree2, (void *) 3, int_cmp);
    tree_insert(tree2, (void *) 7, int_cmp);
    tree_insert(tree2, (void *) 2, int_cmp);
    tree_insert(tree2, (void *) 4, int_cmp);
    tree_insert(tree2, (void *) 6, int_cmp);
    tree_insert(tree2, (void *) 8, int_cmp);
    /*
         5
       /   \ 
      3     7
     / \   / \
    2   4 6   8
        
*/

    bfs = tree_dfs(tree2);

    for (int i = 0; i<bfs->size; i++){
        void* data = list_get(bfs, i);
        printf("%p\n",data);
    }

    printf("3");
    TreeNode *node = tree_search(tree2, (void *) 3, int_cmp);
    if(node == NULL){printf("failed...\n");}
    if(node->data != 3){printf("Node data is not 3\n");}

    printf("5");
    node = tree_search(tree2, (void *) 5, int_cmp);
    if(node == NULL){printf("failed...\n");}
    if(node->data != 5){printf("Node data is not 5\n");}

    printf("8");
    node = tree_search(tree2, (void *) 8, int_cmp);
    if(node == NULL){printf("failed...\n");}
    if(node->data != 8){printf("Node data is not 8\n");}

    printf("1");
    node = tree_search(tree2, (void *) 1, int_cmp);
    if(node != NULL){printf("failed...should be null\n");}
    tree_destroy(tree2);
 
    /*
    printf("%p, %p, %p \n", &dat1, &dat2, &dat3);
    tree_insert(tree,&dat1,&int_cmp);
    List* bfs = tree_bfs(tree);
    for (int i = 0; i<bfs->size; i++){
        printf("%p\n",list_get(bfs, i));
    }
    list_destroy(bfs);
    tree_insert(tree,&dat2,&int_cmp);
    List* bfs2 = tree_bfs(tree);
    for (int i = 0; i<bfs2->size; i++){
        printf("%p\n",list_get(bfs2, i));
    }
    list_destroy(bfs2);
    tree_insert(tree,&dat3,&int_cmp);
    List* bfs3 = tree_bfs(tree);
    for (int i = 0; i<bfs3->size; i++){
        printf("%p\n",list_get(bfs3, i));
    }
    list_destroy(bfs2);
    
    tree_destroy(tree);*/
}
