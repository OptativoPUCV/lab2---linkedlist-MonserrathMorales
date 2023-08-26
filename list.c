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

void * prevList(List * list) {
    if(list->current != NULL && list->current->prev != NULL) {
      list->current = list->current->prev;
      return (list->current->data);
    }
    return NULL;
}

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
/* elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el **dato** del nodo eliminado.
> **Nota**: El current debe quedar apuntando al nodo siguiente del eliminado. */
void * popCurrent(List * list) {
  // caso 1: list->current == NULL
    if(list->current != NULL) {
      void * dato = list->current->data;
      
      // caso 2: list->current->prev == NULL (current==head)
      if(list->current == list->head) {
        list->head = list->current->next;
        if (list->head != NULL) {
          list->head->prev = NULL;
        }
      }
      // caso 3: list->current->next == NULL (current==tail)
      else if(list->current == list->tail) {
        list->tail = list->current->prev;
        if(list->tail != NULL) {
          list->tail->next = NULL;
        }
      }
      // (current!=head && head!=tail)
      else {
        Node * aux = list-> head;
        while(aux->next != list->current && aux->next != NULL) {
          aux = aux->next;
        }
        if (list->current->next != NULL) {
          list->current->next->prev = aux;
        }
        else {
          list->tail = aux;
        }
        aux->next = list->current->next;
      }
      // list->current = list->current->next;
      Node *temp = list->current;
      list->current = list->current->next;
      free(temp);
      //list->tail = list->tail->prev;
      return dato;
    }
    return NULL;  
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}