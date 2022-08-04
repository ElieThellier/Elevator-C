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
    // liste chainée avec liste vide *p=NULL; au depart
    PersonList* L=malloc(sizeof(PersonList*));
    L -> person=p;
    L -> next = list;
    return L;
}

PersonList* suppr(PersonList *list){
    // liste chainée avec liste vide *p=NULL; au depart
    PersonList* K=malloc(sizeof(PersonList*));
    if(list->next!=NULL | list->next->next!=NULL){
        K -> person=list->next->person;
        K -> next = list->next->next;
        return K;
    }
    else{
        return list;
    }
}

int taille(PersonList *L){
    if (L==NULL){
        return 0;
    }
    else{
        return taille(L->next)+1;
    }
}