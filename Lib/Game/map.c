/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** map
*/

#include <stdlib.h>
#include "map.h"

bool init_map(map_t *map)
{
    map->data = NULL;
    map->size.x = 0;
    map->size.y = 0;
    return true;
}

void clear_map(map_t *map)
{
    uint32_t total_size = map->size.x * map->size.y;

    if (map->data) {
        for (uint32_t i = 0; i < total_size; ++i)
            clear_tile(&map->data[i]);
        free(map->data);
    }
    init_map(map);
}