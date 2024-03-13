#include <stdio.h>
#include "../../lib/objects/objects.h"

int main()
{
    // creating some customers
    Customer* client1 = customer_create("me", "here");
    Customer* client2 = customer_create("you", "there");
    Customer* client3 = customer_create("me", "but not here");
    Customer* client4 = customer_create("not me", "but there");
    Customer* client5 = customer_create("me", "here again");

    // creating some cars
    Car* car1 = car_create("cupra", "formentor", "ab 666 by");
    Car* car2 = car_create("disney", "flash Mc Queen", "let's gooo");
    Car* car3 = car_create("the best", "martin", "vroom vroom");
    Car* car4 = car_create("ferrari", "connait pas", "plaque de riche");
    Car* car5 = car_create("porcherie", "groin", "je me la peteee");

    // linking cars to customers
    link_car(car1, client1);
    link_car(car2, client2);
    link_car(car3, client3);
    link_car(car4, client4);
    link_car(car5, client5);

    // creating a registry
    int nb_customers = 5;
    Customer** clients = (Customer*[]){client1, client2, client3, client4, client5};

    Registry* reg = registry_create(clients, nb_customers);

    // playing with it

    print_registry(reg);

    // enough !!!

    registry_destroy(reg);


    return 0;
}
