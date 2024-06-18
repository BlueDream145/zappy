/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list_add
*/

// NULL
#include <stdlib.h>

#include "list.h"

static bool push_front(list_t *list, node_t *node);
static bool push_back(list_t *list, node_t *node);
static bool push_at(list_t *list, node_t *node, int index);

bool append_list(list_t *list, void *elem)
{
    return insert_list(list, elem, list->size);
}

bool insert_list(list_t *list, void *elem, int index)
{
    bool res = false;
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return false;
    node->value = elem;
    node->prev = NULL;
    node->next = NULL;
    if (index == 0)
        res = push_front(list, node);
    else if (index == list->size)
        res = push_back(list, node);
    else
        res = push_at(list, node, index);
    if (res)
        ++list->size;
    return res;
}

/* Push in front of list */
static bool push_front(list_t *list, node_t *node)
{
    if (list->head)
        list->head->prev = node;
    node->next = list->head;
    list->head = node;
    return true;
}

/* Push at end of list */
static bool push_back(list_t *list, node_t *node)
{
    node_t *prev = get_list(list, list->size - 1);

    prev->next = node;
    node->prev = prev;
    return true;
}

/* Push at given index (excluding first and end) */
static bool push_at(list_t *list, node_t *node, int index)
{
    node_t *next = get_list(list, index);

    if (!next) {
        free(node);
        return false;
    }
    if (next->prev) {
        node->prev = next->prev;
        next->prev->next = node;
    }
    next->prev = node;
    node->next = next;
    return true;
}