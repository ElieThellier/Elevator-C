#include "elevator.h"
#include "person.h"
#include <stdlib.h>
#include <stdio.h> //pour les debug-test avec printf

void stepElevator(Building *b){
    /*
cette fonction simule le déplacement de l’ascenseur :
si l’étage courant de l’ascenseur correspond à sa destination, les personnes entrent et sortent de la cabine
sinon, l’étage courant est incrémenté ou décrémenté de 1 pour se rapprocher de sa destination
    */

    if(b->elevator->currentFloor==b->elevator->targetFloor){
        // on ne doit pas lancer la fonction d'entrée dans l'ascenseur si il n'y a personne dans la liste d'attente de l'étage
        if(b->waitingLists[b->elevator->currentFloor]!=NULL){
            b->waitingLists[b->elevator->currentFloor]=enterElevator(b->elevator,b->waitingLists[b->elevator->currentFloor]);
        }
        // on ne doit pas lancer la fonction de sortie dans l'ascenseur si il n'y a personne dans l'ascenseur
        if(b->elevator->persons!=NULL){
            exitElevator(b->elevator); // je sais pas pk on devrait garder la liste des personnes qui sortent de l'ascenseur
        }
    }
        
    else{
        // on souhaite monter
        if (b->elevator->currentFloor<b->elevator->targetFloor){
            b->elevator->currentFloor=(b->elevator->currentFloor+1)%(b->nbFloor);
        }
        // on souhaite descendre
        else if(b->elevator->currentFloor>b->elevator->targetFloor){
            b->elevator->currentFloor=(b->elevator->currentFloor-1)%(b->nbFloor);
        }
    }
}

// Permet de créer l'ascenseur et de l'initialiser
Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *e = malloc(sizeof(Elevator*));
    e -> capacity= capacity;
    e -> currentFloor= currentFloor;
    e -> targetFloor= 0;
    e -> persons = persons;
    return e;
}

// Permet de créer l'immeuble et de l'initialiser
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building* b = malloc(sizeof(Building*));
    b -> nbFloor = nbFloor;
    b -> elevator = elevator;
    b -> waitingLists = waitingLists;
    return b;
}

PersonList* exitElevator(Elevator *e){
    /*
cette fonction renvoie la liste des personnes qui sortent de l’ascenseur
restent dans l’ascenseur les personnes qui ne sont pas sorties
    */

    // definition de la liste des personnes sortantes
    PersonList* personsout = malloc(sizeof(PersonList*));

    // on regarde si il y a au moins 1 personne dans l'ascenseur
    if(e->persons!=NULL){
        // on regarde si la 1ere personne dans l'ascenseur doit sortir à l'étage courant
        if(e->persons->person->dest==e->currentFloor){
            // si oui, on ajoute cette personne dans la liste de ceux qui sortent
            personsout=insert(e->persons->person,personsout);
            // et on enlève cette personne de l'ascenseur
            e->persons=suppr(e->persons);
        }
    }
    // on regarde si il y a au moins 2 personnes dans l'ascenseur
    if(e->persons!=NULL){
        if(e->persons->next!=NULL){
            // puis pareil qu'avant mais pour la deuxième personne de l'ascenseur
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
    /*
cette fonction fait entrer dans l’ascenseur les personnes qui attendent (waitingList)
et renvoie la nouvelle liste d’attente (i.e. la liste initiale moins les personnes qui sont entrées dans l’ascenseur)
L’ascenseur ne peut pas accueillir plus de personnes que sa capacité maximale
    */

    while (waitingList->next!=NULL & taille(e->persons)<e->capacity){
        // on fait rentrer les personnes de la liste d'attente dans l'ascenceur
        e->persons=insert(waitingList->person,e->persons);
        // on enleve les personnes entrées de la liste d'attente
        waitingList=waitingList->next;
    }
    // cas s'il ne reste qu'une personne dans la liste d'attente (waitinList->next==NULL)
    if(waitingList->next==NULL & taille(e->persons)<e->capacity){
        e->persons=insert(waitingList->person,e->persons);
        waitingList=waitingList->next;
    }
    return waitingList;
}