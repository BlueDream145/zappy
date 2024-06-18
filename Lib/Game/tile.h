/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tile
*/

#pragma once

// list_t
#include <List/list.h>

#include "object.h"

/* tile_t contains an object list that are currently on the game tile */
typedef struct tile_s {
    list_t list;
    uint32_t objs[OBJ_TOTAL];
} tile_t;

bool init_tile(tile_t *tile);
void clear_tile(tile_t *tile);

/* Objects list API */
void add_tile_object(tile_t *tile, object_type_t type);
bool remove_tile_object(tile_t *tile, object_type_t type);
uint32_t get_total_objs_tile(tile_t *tile);