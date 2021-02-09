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

node *list_index(node *head, size_t i) {
    if(i == 0) {
        return head;
    }
    if(head->next != NULL) {
        return list_index(head->next, i-1);
    }
    return NULL;
}

size_t list_len(node *head) {
    if(head->next != NULL) {
        return list_len(head->next) + 1;
    }
    return 1;
}

bool list_contains(node *head, int value) {
    if (list_find != NULL) {
        return true;
    }
    return false;
}

node *list_get_tail(node *head) {
    if(head->next != NULL) {
        return list_get_tail(head->next);
    }
    return head;
}

void list_remove_all(node *head, int value) {
    if (head->value == value) {
        if(head->next != NULL) {
            list_remove_all(head->next, value);
        }
        list_remove(head);
    }
}

int *list_to_array(node *head) {
    int *arr = malloc(sizeof(int)*list_len(head));
    
}