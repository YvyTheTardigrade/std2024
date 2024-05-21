#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "./../list/list.h"
#include "hash.h"


#define NULL_ASSERT(ptr, name, returned_value) if(ptr == NULL){\
		printf("the pointer %s is null\n", name);\
		return returned_value;\
}
// TODO: Implement

unsigned long int hashFunction(void *key){
    char* K = key;
    unsigned long int h = 0;
    unsigned long int pow = 1;
    for(int i = 0; i<strlen(K); i++){
        h += pow * ((int)K[i] - 96); // on converti le caractère en num dans la base ascii
                                    // ( le 'a' à pour valeur 97 d'où le - 96)
        pow *= 26;                          
    }
    return h;
}
// table de hachage 


HashTable *hashCreate(int size, unsigned long int (*hashFunction)(void *)){

    HashTable* ht_s = malloc(sizeof(HashTable));
    NULL_ASSERT(ht_s, "to the structure hashtable", NULL);

    void** HT = calloc(size ,  sizeof(void*));
    NULL_ASSERT(HT, "to the HASH TABLE", NULL);

    ht_s->HT = HT;
    ht_s->size = size;
    ht_s->hashFunction = hashFunction;

    return ht_s;
}


void hash_destroy(HashTable *table){
    free(table->HT);
    free(table);
}

void hash_insert(HashTable *table, void *key, void* data){
    NULL_ASSERT(table, "to the table", );

    unsigned long int index = table->hashFunction(key);
    /*
    if(index >= table->size){
        printf("the key hashing failed to match with an index in the hash table\n");
        return;
    }*/
    index = index % table->size;
    table->HT[index] = data;

    return;
}

void hash_delete(HashTable *table, void *key){
    NULL_ASSERT(table, "to the table", );

    unsigned long int index = table->hashFunction(key);
    /*
    if(index >= table->size){
        printf("the key hashing failed to match with an index in the hash table\n");
        return;
    }*/
    index = index % table->size;
    table->HT[index] = NULL;
    return;
}


void *hash_get(HashTable *table, void *key){
    NULL_ASSERT(table, "to the table", NULL);

    unsigned long int index = table->hashFunction(key);
    printf("key : %s, hash code : %ld\n", (char*) key, index);

    /*if(index >= table->size){
        printf("the key hashing failed to match with an index in the hash table\n");
        return NULL;
    }*/
    index = index % table->size;

    NULL_ASSERT(table->HT[index], "at the corresponding key", NULL);

    return table->HT[index];
}

int hash_size(HashTable *table){
    return table->size;
}


// table de hachage avec chaînage externe
HashTableChain *hashChainCreate(int size, unsigned long int (*hashFunction)(void *)){
    HashTableChain* ht_s = malloc(sizeof(HashTableChain));
    NULL_ASSERT(ht_s, "to the structure hashtable", NULL);

    List** HT = calloc(size ,  sizeof(List*));
    NULL_ASSERT(HT, "to the HASH TABLE", NULL);

    List** keys = calloc(size ,  sizeof(List*));
    NULL_ASSERT(HT, "to the HASH TABLE", NULL);
    

    ht_s->HT = HT;
    ht_s->keys = keys;
    ht_s->size = size;
    ht_s->hashFunction = hashFunction;

    return ht_s;
}

void hash_chain_destroy(HashTableChain *table){
    for(int i = 0; i < table->size; i++){
        if(table->HT[i] == NULL){
            continue;
        }
        list_destroy(table->HT[i]);
        if(table->HT[i] == NULL){
            continue;
        }
        list_destroy(table->keys[i]);
    }

    free(table->HT);
    free(table->keys);
    free(table);
    return;
}


void hash_chain_insert(HashTableChain *table, void *key, void *data){
    NULL_ASSERT(table, "to the table", );

    unsigned long int index = table->hashFunction(key);
    /*
    if(index >= table->size){
        printf("the key hashing failed to match with an index in the hash table\n");
        return;
    }*/
    index = index % table->size;
    if(table->HT[index] == NULL){
        table->HT[index] = list_create();
    }

    if(table->keys[index] == NULL){
        table->keys[index] = list_create();
    }


    list_append(table->HT[index], data);
    list_append(table->keys[index], key);

    return;
}
void hash_chain_delete(HashTableChain *table, void *key){
    NULL_ASSERT(table, "to the table", );

    unsigned long int index = table->hashFunction(key);
    /*
    if(index >= table->size){
        printf("the key hashing failed to match with an index in the hash table\n");
        return;
    }*/

    index = index % table->size;
    unsigned long int id_to_del = list_indexOf(table->keys[index], key);
    if(id_to_del == -1){
        printf("the key doesn't exists\n");
        return;
    }
    list_set(table->HT[index],NULL, id_to_del);
    list_set(table->keys[index],NULL, id_to_del);
    //table->HT[index] = NULL;
    return;

}
void *hash_chain_get(HashTableChain *table, void *key){
    NULL_ASSERT(table, "to the table", NULL);

    unsigned long int index = table->hashFunction(key);

    /*
    if(index >= table->size){
        printf("the key hashing failed to match with an index in the hash table\n");
        return NULL;
    }*/
    index = index % table->size;
    NULL_ASSERT(table->HT[index], "at the corresponding key", NULL);

    unsigned long int id_to_get = list_indexOf(table->keys[index], key);
    if(id_to_get == -1){
        printf("the key doesn't exists\n");
        return NULL;
    }

    return list_get(table->HT[index], id_to_get);
}


int hash_chain_size(HashTableChain *table){
    int size;
    for(int i = 0; i < table->size; i++){
        if(table->HT[i] == NULL) continue;
        size += table->HT[i]->size;
    }

    return size;
}