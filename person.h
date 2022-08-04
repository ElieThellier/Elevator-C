#ifndef PERSON_H
#define PERSON_H

typedef struct _Person {
    int src;  // étage source de la personne
    int dest; // étage destination de la personne
} Person;

typedef struct _PersonList {
    Person *person;
    struct _PersonList *next; // liste chainée
} PersonList;

Person* createPerson(int src, int dest);
PersonList* insert(Person *p, PersonList *list);
PersonList* suppr(PersonList *list);
int taille(PersonList *L);

#endif