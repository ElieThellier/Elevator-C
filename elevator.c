#include "elevator.h"
#include "person.h"
#include <stdlib.h>
#include <stdio.h>

void stepElevator(Building *b){
    if(b->elevator->currentFloor==b->elevator->targetFloor){
        
        if(b->waitingLists[b->elevator->currentFloor]!=NULL){
            b->waitingLists[b->elevator->currentFloor]=enterElevator(b->elevator,b->waitingLists[b->elevator->currentFloor]);
        }
        if(b->elevator->persons!=NULL){
            exitElevator(b->elevator); // je sais pas pk on devrait garder la liste des personnes qui sortent de l'ascenseur
        }
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
    if(e->persons!=NULL){
        if(e->persons->person->dest==e->currentFloor){
            personsout=insert(e->persons->person,personsout);
            e->persons=suppr(e->persons);
        }
    }
    if(e->persons!=NULL){
        if(e->persons->next!=NULL){
            if(e->persons->next->person->dest==e->currentFloor){
                personsout=insert(e->persons->next->person,personsout);
                e->persons->next=suppr(e->persons->next);
                }
        }
    }
    if(e->persons!=NULL){
        if(e->persons->next!=NULL){
            if(e->persons->next->next!=NULL){
                if(e->persons->next->next->person->dest==e->currentFloor){
                    personsout=insert(e->persons->next->next->person,personsout);
                    e->persons->next->next=suppr(e->persons->next->next);
                }
            }
        }
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
    }
    if(waitingList->next==NULL & taille(e->persons)<e->capacity){
        e->persons=insert(waitingList->person,e->persons);
        waitingList=waitingList->next;
    }
    return waitingList;

}