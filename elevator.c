#include "elevator.h"
#include <stdlib.h>

void stepElevator(Building *b){
    
}

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *e = malloc(sizeof(Elevator));
    e -> capacity= capacity;
    e -> currentFloor= currentFloor;
    e -> targetFloor= currentFloor; //je sais pas encore quoi mettre
    e -> persons = persons;
    return e;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building* b = malloc(sizeof(Building));
    b -> nbFloor = nbFloor;
    b -> elevator = elevator;
    b -> waitingLists = waitingLists;
    return b;
}

PersonList* exitElevator(Elevator *e){
    PersonList* L;
    return L;
}

PersonList* enterElevator(Elevator *e, PersonList *waitingList){
    PersonList* L;
    return L;
}