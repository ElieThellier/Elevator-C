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
    if(list!=NULL){
        PersonList *result=list->next;
        free(list);
        return result;
    }
    else{
        return NULL;
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