/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tile
*/

#include <stdlib.h>
#include "tile.h"

void add_tile_object(tile_t *tile, object_type_t type)
{
    if (tile) {
        tile->objs[type] += 1;
    }
}

bool remove_tile_object(tile_t *tile, object_type_t type)
{
    if (!(tile) || !(tile->objs[type]))
        return false;
    tile->objs[type] -= 1;
    return true;
}