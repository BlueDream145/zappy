/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list_remove
*/

// NULL
#include <stdlib.h>

#include "list.h"

void *pop_list(list_t *list)
{
    return erase_list(list, list->size - 1);
}

void *erase_list(list_t *list, int index)
{
    node_t *node = get_list(list, index);
    void *elem = node ? node->value : NULL;

    if (!node)
        return NULL;
    if (!node->prev)
        list->head = node->next;
    else
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    --list->size;
    return elem;
}

bool remove_node(list_t *list, void *elem)
{
    int index = 0;
    node_t *node = list->head;

    if (!list || !elem)
        return false;
    while (node != NULL) {
        if (node->value == elem) {
            erase_list(list, index);
            free(node);
            return true;
        }
        node = node->next;
        index++;
    }
    return false;
}