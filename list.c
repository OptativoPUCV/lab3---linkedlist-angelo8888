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


List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    if (newList != NULL) {
        newList->head = NULL;
        newList->tail = NULL;
        newList->current = NULL;
    }
    return newList;
}

void * firstList(List * list) {
    if (list != NULL && list->head != NULL) {
        list->current = list->head;
        return list->head->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list != NULL && list->current != NULL && list->current->next != NULL) {
        list->current = list->current->next;
        return list->current->data;
    }
    return NULL;
}

void * lastList(List * list) {
    if (list != NULL && list->tail != NULL) {
        list->current = list->tail;
        return list->tail->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list != NULL && list->current != NULL && list->current->prev != NULL) {
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    if (list != NULL && newNode != NULL) {
        if (list->head == NULL) {
            list->head = newNode;
            list->tail = newNode;
        } else {
            newNode->next = list->head;
            list->head->prev = newNode;
            list->head = newNode;
        }
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void* data) {
    Node* newNode = createNode(data);
    if (list != NULL && newNode != NULL && list->current != NULL) {
        if (list->current == list->tail) {
            list->tail = newNode;
        } else {
            newNode->next = list->current->next;
            list->current->next->prev = newNode;
        }
        newNode->prev = list->current;
        list->current->next = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}


void* popCurrent(List * list) {
    if (list != NULL && list->current != NULL) {
        Node* nodeToRemove = list->current;
        void* data = nodeToRemove->data;

        if (nodeToRemove == list->head) {
            list->head = nodeToRemove->next;
            if (list->head != NULL)
                list->head->prev = NULL;
        } else if (nodeToRemove == list->tail) {
            list->tail = nodeToRemove->prev;
            if (list->tail != NULL)
                list->tail->next = NULL;
        } else {
            nodeToRemove->prev->next = nodeToRemove->next;
            nodeToRemove->next->prev = nodeToRemove->prev;
        }

        list->current = nodeToRemove->next;
        free(nodeToRemove);
        return data;
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}