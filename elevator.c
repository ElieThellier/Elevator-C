#include "elevator.h"
#include "person.h"
#include <stdlib.h>
#include <stdio.h>

void stepElevator(Building *b){
    
    if(b->elevator->currentFloor==b->elevator->targetFloor){
        PersonList* test=exitElevator(b->elevator); // je sais pas pk on devrait garder la liste des personnes qui sortent de l'ascenseur
        b->waitingLists[b->elevator->currentFloor]=enterElevator(b->elevator,b->waitingLists[b->elevator->currentFloor]);
    }
        
    else{
        if (b->elevator->currentFloor<b->elevator->targetFloor){
            b->elevator->currentFloor=(b->elevator->currentFloor+1)%(b->nbFloor);
        }
        else if(b->elevator->currentFloor>b->elevator->targetFloor){
            b->elevator->currentFloor=(b->elevator->currentFloor-1)%(b->nbFloor);
        }
        
    }
    
}

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *e = malloc(sizeof(Elevator*));
    e -> capacity= capacity;
    e -> currentFloor= currentFloor;
    e -> targetFloor= 0;
    e -> persons = persons;
    return e;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building* b = malloc(sizeof(Building*));
    b -> nbFloor = nbFloor;
    b -> elevator = elevator;
    b -> waitingLists = waitingLists;
    return b;
}

PersonList* exitElevator(Elevator *e){
    PersonList* personsout = malloc(sizeof(PersonList*));
    // on regarde chaque personne dans l'ascenseur
    PersonList* temp=malloc(sizeof(PersonList*));
    while(temp->next!=NULL){
        // si une personne doit sortir
        if(temp->person->dest==e->currentFloor){
            // on l'ajoute dans la liste des personnes qui sortent
            personsout=insert(temp->person,personsout);
            // et on l'enleve de l'ascenseur
            temp=suppr(temp);
        }
        // sinon, on regarde la personne suivante
        else{
            temp++;
        }
        e->persons=temp;
    }
    
    // on renvoie la liste de ceux qui sortent de l'ascenseur (on a modifié celle de ceux qui restent dedans)
    return personsout;
}

PersonList* enterElevator(Elevator *e, PersonList *waitingList){
    while (waitingList->next!=NULL & taille(e->persons)<e->capacity){
        // on fait rentrer les persons de la liste d'attente dans l'ascenceur
        e->persons=insert(waitingList->person,e->persons);
        // on enleve les persons de la liste d'attente
        waitingList=waitingList->next;
        //? waitingList++;
    }
    return waitingList;
}