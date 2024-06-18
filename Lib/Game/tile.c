/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tile
*/

#include "tile.h"

static void init_list_objs(tile_t *tile)
{
    if (!(tile))
        return;
    for (int i = 0; i < OBJ_TOTAL; i++)
        tile->objs[i] = 0;
}

bool init_tile(tile_t *tile)
{
    if (!init_list(&tile->list))
        return false;
    init_list_objs(tile);
    return true;
}

void clear_tile(tile_t *tile)
{
    while (remove_tile_object(tile, 0));
}

uint32_t get_total_objs_tile(tile_t *tile)
{
    uint32_t res = 0;

    if (!(tile))
        return (0);
    for (int i = 0; i < OBJ_TOTAL; i++)
        res += tile->objs[i];
    return (res);
}