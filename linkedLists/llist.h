#ifndef _LLIST_H
#define _LLIST_H


#include <stdlib.h>

struct node {
    int value;
    struct node *next;
    struct node *prev;
};

typedef struct node node;

// Makes a new node with the given value and NULL
// next and prev pointers.
node *node_make(int value);


// Your other function prototypes go here, between
// the #ifndef and the #endif.
node *list_insert(node *prev, int value);
void list_print(const node *head);
node *list_find(node *head, int value);
void list_remove(node *n);
void list_free(node *head);
//optionals
node *list_index(node *head, size_t i);
size_t list_len(node *head);
bool list_contains(node *head, int value);
node *list_get_tail(node *head);
void list_remove_all(node *head, int value);
int *list_to_array(node *head);

#endif