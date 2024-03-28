#include <stdio.h>

#include "../../lib/list/list.h"
#include "../../lib/queue/queue.h"
#include "../../lib/stack/stack.h"

void list_fn()
{
    List* my_list = list_create();
    int len = list_size(my_list);

    printf("size : %d\n", len);

    char* txt1 = "123";
    char* txt2 = "1.2";
    char* txt3 = "bonjour tt le monde";
    char* txt4 = "bonsoir tt le monde";

    void* data1 = (void*) &txt1;
    void* data2 = (void*) &txt2;
    void* data3 = (void*) &txt3;
    void* data4 = (void*) &txt4;

    list_append(my_list, data1);
    list_append(my_list, data2);
    list_append(my_list, data3);

    len = list_size(my_list);

    printf("size : %d\n", len);

    
    for(int i = 0; i < len; i++){ 
        char* recovered_data =  list_get(my_list, i);
        printf("txt%d : %s\n", i, recovered_data);
    }
    
    void* elt_to_test1 = data1;
    char* elt_to_test2 = data4;

    printf("y'a t il \"123\" dans la liste ? (1 si oui, 0 sinon) : %d \n", list_contains(my_list, elt_to_test1));
    printf("y'a t il \"bonsoir tt le monde\" dans la liste ? (1 si oui, 0 sinon) : %d \n", list_contains(my_list, elt_to_test2));

    printf("où se trouve \"123\" dans la liste ? (-1 si n'y est pas) : %d \n", list_indexOf(my_list, elt_to_test1));
    printf("où se trouve \"bonsoir tt le monde\" dans la liste ? (-1 si n'y est pas) : %d \n", list_indexOf(my_list, elt_to_test2));

    printf("puisque \"bonsoir tout le monde\" ne doit pas y être, nous allons le rajouter a l'indice 5 : \n");
    
    list_insert(my_list, 5, elt_to_test2);

    printf("oups ... pas le bon indice...réessayons en position 2 : \n");

    list_insert(my_list, 2, elt_to_test2);

    printf("ca semble bon ... vérifions s'il y est et où : \n");
    
    printf("y'a t il \"bonsoir tt le monde\" dans la liste ? (1 si oui, 0 sinon) : %d \n", list_contains(my_list, elt_to_test2));
    printf("où se trouve \"bonsoir tt le monde\" dans la liste ? (-1 si n'y est pas) : %d \n", list_indexOf(my_list, elt_to_test2));

    printf("la taille actuelle est : %d\n", list_size(my_list));
    list_delete(my_list, 1);
    printf("on supprime l'indice 1 et la nouvelle taille est : %d\n", list_size(my_list));

    printf("comme je suis un co***** je vais delete en trop heheheheeee!!!\n");
    printf("et de 1\n");
    list_delete(my_list, 0);
    printf("et de2\n");
    list_delete(my_list, 0);
    printf("et de 3\n");
    list_delete(my_list, 0);
    printf("et de 4\n");
    list_delete(my_list, 0);
    printf("et de 5\n");
    list_delete(my_list, 0);



    printf("assez joué on détruit tout...");
    list_destroy(my_list);

    return;
}

void queue_fn()
{
    Queue* my_queue = queue_create();
    
    int nb1 = 1901;
    int nb2 = 123;
    int nb3 = 666;
    int nb4 = 12345;

    void* data1 = (void*) &nb1;
    void* data2 = (void*) &nb2;
    void* data3 = (void*) &nb3;
    void* data4 = (void*) &nb4;

    printf("la taille actuelle est : %d\n", queue_size(my_queue));
    queue_enqueue(my_queue, data1);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));
    queue_enqueue(my_queue, data2);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));
    queue_enqueue(my_queue, data3);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));

    printf("on dequeue un peu...\n");
    int* recovered_data = queue_dequeue(my_queue);
    printf("j'ai récupéré l'élément le plus vieux (normalement) : %d\n", *recovered_data);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));

    recovered_data = queue_dequeue(my_queue);
    printf("j'ai récupéré l'élément le plus vieux (normalement) : %d\n", *recovered_data);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));

    recovered_data = queue_dequeue(my_queue);
    printf("j'ai récupéré l'élément le plus vieux (normalement) : %d\n", *recovered_data);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));

    queue_enqueue(my_queue, data4);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));

    recovered_data = queue_dequeue(my_queue);
    printf("j'ai récupéré l'élément le plus vieux (normalement) : %d\n", *recovered_data);
    printf("la taille actuelle est : %d\n", queue_size(my_queue));

    printf("comme d'hab de vais dequeue en trop : \n");
    recovered_data = queue_dequeue(my_queue);
    
    printf("terminé...\n");
    queue_destroy(my_queue);
    return;
}

void stack_fn()
{
    Stack * my_stack = stack_create();
    float nb1 = 1901.55;
    float nb2 = 123.2;
    float nb3 = 666.666;
    float nb4 = 123.45;

    void* data1 = (void*) &nb1;
    void* data2 = (void*) &nb2;
    void* data3 = (void*) &nb3;
    void* data4 = (void*) &nb4;

    printf("la taille actuelle est : %d\n", stack_size(my_stack));
    stack_push(my_stack, data1);
    printf("la taille actuelle est : %d\n", stack_size(my_stack));
    stack_push(my_stack, data2);
    printf("la taille actuelle est : %d\n", stack_size(my_stack));
    stack_push(my_stack, data3);
    printf("la taille actuelle est : %d\n", stack_size(my_stack));

    float* recovered_data = stack_pop(my_stack);
    printf("j'ai récupéré l'élément du haut de la pile (normalement) : %f\n", *recovered_data);
    printf("la taille actuelle est : %d\n", stack_size(my_stack));

    recovered_data = stack_pop(my_stack);
    printf("j'ai récupéré l'élément du haut de la pile (normalement) : %f\n", *recovered_data);
    printf("la taille actuelle est : %d\n", stack_size(my_stack));

    recovered_data = stack_pop(my_stack);
    printf("j'ai récupéré l'élément du haut de la pile (normalement) : %f\n", *recovered_data);
    printf("la taille actuelle est : %d\n", stack_size(my_stack));

    stack_push(my_stack, data4);
    printf("la taille actuelle après ajout du dernier elt est : %d\n", stack_size(my_stack));

    recovered_data = stack_pop(my_stack);
    printf("j'ai récupéré l'élément du haut de la pile (normalement) : %f\n", *recovered_data);
    printf("la taille actuelle est : %d\n", stack_size(my_stack));
    printf("on a poper et la taille actuelle est : %d\n", stack_size(my_stack));

    printf("pour finir on pop un peu en trop !!!\n");
    recovered_data = stack_pop(my_stack);

    printf("finito\n");

    stack_destroy(my_stack);
    return;
}

int main()
{
    // List
    list_fn();

    // Queue
    queue_fn();

    // Stack
    stack_fn();

    return 0;
}
