/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** object
*/

#pragma once

// bool
#include <stdbool.h>
// uint32
#include <stdint.h>

typedef enum {
    OBJ_FOOD = 0,
    OBJ_LINEMATE,
    OBJ_DERAUMERE,
    OBJ_SIBUR,
    OBJ_MENDIANE,
    OBJ_PHIRAS,
    OBJ_THYSTAME,
    OBJ_TOTAL
} object_type_t;

static const char * const object_type_names[OBJ_TOTAL] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

typedef struct object_s {
    object_type_t type;
} object_t;

bool init_object(object_t *object, object_type_t type);
void clear_object(object_t *object);