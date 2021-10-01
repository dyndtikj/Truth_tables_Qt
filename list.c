#include "list.h"
#include <stdlib.h>

void list_init(list_t *list)
{
    list->head = NULL;
}

static node_t *new_node(struct token data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    return node;
}

void list_append(list_t *list, struct token data)
{
    node_t *head = list->head,
    *node = new_node(data);

    if (head){
        for (; head->next; head = head->next); // Доходим до последнего узла
        head->next = node;
    }else list->head = node;
}

struct token list_get(list_t *list, unsigned index)
{
    node_t *head = list->head;
    unsigned i = 0;

    for (; head; head = head->next, i++){
        if (i == index) {
            return head->data;
        }
    }
}

void list_pop_tail(list_t *list)
{
    node_t *head = list->head;

    if (head->next) {
        for (; head->next->next; head = head->next); //goto the last second node
        free(head->next->data._mas);
        free(head->next);
        head->next = NULL;
    }
}

void list_delete(list_t* list)
{
    node_t* head = list->head;
    while (head->next) {
        list_pop_tail(list);
    }
    free(head->data._mas);
    free(head);
    list->head = NULL;
}
