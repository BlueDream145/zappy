/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#pragma once

#include "tile.h"
#include "v2u.h"

/* map_t
    - data : 1D array of tile
    - size : size of array in 2D space
*/
typedef struct map_s {
    tile_t *data;
    v2u_t size;
} map_t;

bool init_map(map_t *map);
void clear_map(map_t *map);

/* Map data API */
bool resize_map(map_t *map, v2u_t size);
tile_t *get_tile(map_t *map, v2u_t pos);