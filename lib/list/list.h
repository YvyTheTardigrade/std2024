#ifndef LIST_H
#define LIST_H

typedef struct listNode
{
    void* data;
    struct listNode* next;
    struct listNode* previous;

} ListNode;

typedef struct list
{
    int size;
    ListNode* FirstNode;
    ListNode* LastNode;
    
} List;

List *list_create();
int list_size(List *list);
void *list_get(List *list, int index);
void list_set(List *list,void* data, int index);
int list_contains(List *list, void *data);
void list_append(List *list, void *data);
void list_insert(List *list, int index, void *data);
int list_indexOf(List *list, void *data);
void list_delete(List *list, int index);
void list_destroy(List *list);

#endif
