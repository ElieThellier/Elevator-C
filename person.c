#include"person.h"
#include<stdlib.h>

Person* createPerson(int src, int dest){
    Person* p=malloc(sizeof(Person));
    p -> src = src;
    p -> dest = dest;
    return p;
}

PersonList* insert(Person *p, PersonList *list){
    // liste chainée avec liste vide char *p=NULL; au depart
    PersonList* L=malloc(sizeof(PersonList));
    L -> person=p;
    L -> next = list;
    return L;
}