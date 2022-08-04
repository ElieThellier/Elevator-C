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
    // on créer un nouvelle liste chainée avec comme valeur la personne que l'on veut ajouter et comme extension la liste de base
    PersonList* L=malloc(sizeof(PersonList*));
    L -> person=p;
    L -> next = list;
    return L;
}

PersonList* suppr(PersonList *list){
    // si la liste d'entrée est non nulle, on garde en memoire l'extension de cette liste, on libère la liste de base et on renvoie le pointeur sur la liste extension
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
    // cas de base (taille(liste_vide)=0)
    if (L==NULL){
        return 0;
    }
    // récursion
    else{
        return taille(L->next)+1;
    }
}