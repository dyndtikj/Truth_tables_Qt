#ifndef LIST_H
#define LIST_H 1
#include "Check_functions.h"

typedef struct node {
    struct token data;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
} list_t;

void list_init(list_t* list);

void list_append(list_t* list, struct token data);

void list_pop_tail(list_t* list);

void list_delete(list_t* list);

struct token list_get(list_t * list, unsigned index);
#endif
