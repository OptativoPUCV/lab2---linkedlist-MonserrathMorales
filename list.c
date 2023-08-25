#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = 0;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if(list->head != NULL) {
      list->current = list->head;
      return (list->head->data);
    }
    return NULL;
}

void * nextList(List * list) {
    if(list->current != NULL && list->current->next != NULL) {
      list->current = list->current->next;
      return (list->current->data);
    }
    return NULL;
}

void * lastList(List * list) {
    if(list->tail != NULL) {
      list->current = list->tail;
      return (list->tail->data);
    }
    return NULL;
}
/* retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo. */
void * prevList(List * list) {
    if(list->current != NULL && list->current->prev != NULL) {
      list->current = list->current->prev;
      return (list->current->data);
    }
    return NULL;
}
/* agrega un dato al comienzo de la lista. */
void pushFront(List * list, void * dato) {
    Node* nodo = createNode(dato);
    nodo->prev = NULL;
    nodo->next = list->head;
  
    if(list->head != NULL) {
      list->head->prev = nodo;
    }
    list->head = nodo;
    list->tail = nodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}
/* agrega un dato a continuación del nodo apuntado por `list->current`. */
void pushCurrent(List * list, void * data) {
    Node * nodo = createNode(data);
    nodo->prev = list->current;
    nodo->next = list->current->next;
  
    if(list->current->next != NULL) {
      list->current->next->prev = nodo;
    }
    list->current->next = nodo;
    list->tail = nodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node* aux = list->head;
    while(aux->next != current) {
      aux = aux->next;
    }
    aux->next = list->current->next;
    free(list->current);
    return (list->current->data);
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}