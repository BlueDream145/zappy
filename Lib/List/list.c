/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list_get
*/

// NULL
#include <stdlib.h>

#include "list.h"

bool init_list(list_t *list)
{
    list->head = NULL;
    list->size = 0;
    return true;
}

void clear_list(list_t *list)
{
    while (pop_list(list));
}

void *at_list(list_t *list, int index)
{
    node_t *node = get_list(list, index);

    return node ? node->value : NULL;
}

node_t *get_list(list_t *list, int index)
{
    node_t *node = list->head;

    while (node != NULL) {
        if (!index)
            return node;
        --index;
        node = node->next;
    }
    return (NULL);
}