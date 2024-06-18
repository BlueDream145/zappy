/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** resources
*/

#include "core.h"
#include <stdlib.h>

static bool is_proba(int value, int threshold);
static void add_obj_map(tile_t *tile, object_type_t type, bool need_add,
                        uint32_t *total_objs);
static uint32_t generate_obj_map(map_t *map, const uint32_t thresholds[]);

void init_map_resources(map_t *map)
{
    const uint32_t thresholds[OBJ_TOTAL] = {
        15, 5, 4, 5, 2, 3, 1
    };

    if (!(map))
        return;
    generate_obj_map(map, thresholds);
}

void update_map_resources(map_t *map)
{
    const uint32_t thresholds[OBJ_TOTAL] = {
        20, 10, 10, 10, 10, 10, 8
    };

    if (!(map))
        return;
    generate_obj_map(map, thresholds);
}

static uint32_t generate_obj_map(map_t *map, const uint32_t thresholds[])
{
    uint32_t objs = 0;

    if (!(map))
        return 0;
    for (uint32_t i = 0; i < (map->size.x * map->size.y); i++) {
        for (int type = 0; type < OBJ_TOTAL; type++)
            add_obj_map(&map->data[i], type,
                        is_proba(rand() % 100, thresholds[type]), &objs);
    }
    return (objs);
}

static bool is_proba(int value, int threshold)
{
    return (value <= threshold);
}

static void add_obj_map(tile_t *tile, object_type_t type, bool need_add,
                        uint32_t *total_objs)
{
    if (tile && !tile->objs[type] && need_add) {
        tile->objs[type] += 1;
        (*total_objs)++;
    }
}