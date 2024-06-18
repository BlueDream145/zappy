/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** list
*/

#pragma once

// bool
#include <stdbool.h>

/* Generic C linked-list node */
typedef struct node_s {
    struct node_s *prev;
    struct node_s *next;
    void *value;
} node_t;

/* Generic C linked-list container */
typedef struct list_s {
    node_t *head;
    int size;
} list_t;

typedef void*(*allocator_t)(void);

/* List
    - init_list : initialize given list
    - at_list : return node's value at index
    - get_list : return node at index
*/
bool init_list(list_t *list);
void clear_list(list_t *list);
void *at_list(list_t *list, int index);
node_t *get_list(list_t *list, int index);

/* List management
    - append_list : insert an element at end of list
    - insert_list : insert an element at given index of list (meaning new node's index will be this one)
    - pop_list : remove the last element of a list and return its internal element
    - erase_list : remove the last element of a list and return its internal element
    - remove_node : remove the first node found in the list with a value equal to elem and free the node
*/
bool append_list(list_t *list, void *elem);
bool insert_list(list_t *list, void *elem, int index);
void *pop_list(list_t *list);
void *erase_list(list_t *list, int index);
bool remove_node(list_t *list, void *elem);