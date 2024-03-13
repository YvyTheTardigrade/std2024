#include "objects.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


Car *car_create(char *brand, char *model, char *license){
    Car* C = malloc(sizeof(Car));
    /*
    C -> brand = malloc(sizeof(brand));
    C -> model = malloc(sizeof(model));
    C -> license = malloc(sizeof(license));
    */
    C -> brand = brand;
    C -> model = model;
    C -> license = license;
    return C;
}
Customer *customer_create(char *name, char *address){
    Customer* client = calloc(1, sizeof(Customer));
    client -> name = name;
    client -> address = address;
    client -> car = NULL;
    return client;

}
Registry *registry_create(Customer **customers, int size){
    
    Registry* registry = malloc(sizeof( Registry));
    registry->customers = customers;
    registry -> size = size;
    return registry;

}

void car_destroy(Car *car){
    /*
    free(car->brand);
    free(car->model);
    free(car->license);*/
    free(car);
    return;

}
void customer_destroy(Customer *customer){

    if (customer->car != NULL){
        car_destroy(customer->car);
    }
    /*
    free(customer->address);
    free(customer->name);*/
    free(customer);
    return;

}
void registry_destroy(Registry *registry){
    for(int i = 0; i < registry->size; i++){
        customer_destroy(registry->customers[i]);
    }
    
    free(registry);
    return;

}

void link_car(Car *car, Customer *customer){
    customer->car = car;
    return;

}
void print_registry(Registry *registry){
    for(int i = 0; i < (registry -> size); i++){
        printf("name : %s, address : %s, car : %s (%s %s)\n",registry -> customers[i] -> name, 
        registry -> customers[i] -> address, 
        registry -> customers[i] -> car -> license, 
        registry -> customers[i] -> car -> brand, 
        registry -> customers[i] -> car -> model);
    }
    return;
}