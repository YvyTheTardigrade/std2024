#ifndef TREE_H
#define TREE_H

#include "./../list/list.h"
#include "./../queue/queue.h"
#include "./../stack/stack.h"

typedef struct treeNode
{
    void* data;
    List* childrens;
} TreeNode;

typedef struct tree
{
    TreeNode* root;
    int size;
    
} Tree;

Tree *tree_create();
TreeNode *tree_search(Tree *tree, void *data, int (*cmp)(void *, void *)); //
void tree_destroy_recursiv(TreeNode* tree);
void tree_destroy(Tree *tree);
void tree_insert(Tree *tree, void *data, int (*cmp)(void *, void *)); // pointeur sur fct qui dit dans quelle branche aller 
void print_free_alloc_nb(void);
List *tree_bfs(Tree *tree);// en largeur : on finit un niveau avant de passer au niveau supérieur en parcourant de gauche a droite
List *tree_dfs(Tree *tree);// en profondeur : on parcour au max la branche de gauche puis on re descent petit a petit jusqu'à la racine pour faire l'arbre droit

#endif