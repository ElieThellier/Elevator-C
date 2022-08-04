#include"person.h"
#include<stdlib.h>
#include<stdio.h>

Person* createPerson(int src, int dest){
    Person* p=malloc(sizeof(Person*));
    p -> src = src;
    p -> dest = dest;
    return p;
}

PersonList* insert(Person *p, PersonList *list){
    // liste chainée avec liste vide char *p=NULL; au depart
    PersonList* L=malloc(sizeof(PersonList*));
    L -> person=p;
    L -> next = list;
    return L;
}

PersonList* suppr(PersonList *list){
    // liste chainée avec liste vide char *p=NULL; au depart
    PersonList* L=malloc(sizeof(PersonList*));
    L -> person=list->next->person;
    L -> next = list->next->next;
    return L;
}

int taille(PersonList *L){
    if (L==NULL){
        return 0;
    }
    else{
        return taille(L->next)+1;
    }
}