#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

node *node_make(int value) {
    node *n = malloc(sizeof(node));
    n->value = value;
    n->next = n->prev = NULL;
    
    return n;
}

node *list_insert(node *prev, int value) {
    node *new = node_make(value);
    new->prev = prev;
    if(prev->next != NULL) {
        prev->next->prev = new;
        new->next = prev->next;
    } else {
        new->next = NULL;
    }
    prev->next = new;
    return new;
}

void list_print(const node *head) {
    printf("%d", head->value);
    if(head->next != NULL)
    {
        list_print(head->next);
    }
}

node *list_find(node *head, int value) {
    if(head->value == value) {
        return head;
    }
    if(head->next != NULL) {
        return(list_find(head->next, value));
    }
    return NULL;
}

void list_remove(node *n) {
    if(n->prev != NULL && n->next != NULL) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    } else if(n->prev != NULL) {
        n->prev->next = NULL;
    } else if(n->next != NULL) {
        n->next->prev = NULL;
    }

    free(n);
}

void list_free(node *head) {
    if(head->next != NULL) {
        list_free(head->next);
    }
    free(head);
}