/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map_data
*/

#include <stdlib.h>
#include "map.h"

bool resize_map(map_t *map, v2u_t size)
{
    uint32_t total_size = size.x * size.y;

    if (!total_size || !(map->data = malloc(sizeof(tile_t) * (total_size))))
        return false;
    map->size = size;
    for (uint32_t i = 0; i < total_size; ++i) {
        if (init_tile(&map->data[i]))
            continue;
        free(map->data);
        init_map(map);
        return false;
    }
    return true;
}

tile_t *get_tile(map_t *map, v2u_t pos)
{
    uint32_t coord = pos.y * map->size.x + pos.x;

    if (pos.x >= map->size.x || pos.y >= map->size.y)
        return NULL;
    return &map->data[coord];
}