#include "elevator.h"
#include "person.h"
#include <stdlib.h>

void stepElevator(Building *b){
    // marche pas
    /*
    while(b->elevator->persons->next!=NULL){
        if(b->elevator->currentFloor==b->elevator->persons->person->dest){
            b->elevator=exitElevator(b->elevator);
            b->waitingLists=enterElevator(b->elevator,b->waitingLists);
        }
        else{
            // ATTENTION CA DOIT ETRE < QUE nbrFloor et ça doit aller vers le bas en fct de la dir de person
            b->elevator->currentFloor++;
        }
        b->elevator->persons++;
    }
    */
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
    PersonList* persons = e->persons;
    int capacity = e->capacity;
    int currentFloor = e->currentFloor;
    
    while (persons->next!=NULL){
        if (e->persons->person->dest==currentFloor){
        // on enlève les person qui sortent de persons
            e->persons->person=e->persons->next;
        }
        persons++;
    }
    
    // on renvoie ceux qui restent dans l'ascenseur
    return persons;
}

PersonList* enterElevator(Elevator *e, PersonList *waitingList){
    while (waitingList->next!=NULL){
        // si y'a de la capacité dans l'ascenseur
        if (taille(e->persons)<e->capacity){
            // on fait rentrer les persons de la liste d'attente
            insert(waitingList->person,e->persons);
            // on enleve les persons de la liste d'attente
            waitingList->person=waitingList->next;
        }
        waitingList++;
    }
    return waitingList;
}