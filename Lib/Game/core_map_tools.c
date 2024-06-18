/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core_map_tools
*/

#include "core.h"
#include "object.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

static void fill_obj_format(char **format_content, tile_t *tile,
                            uint32_t *format_idx, int nb_player);
static uint32_t get_format_object_size(object_type_t type);
static uint32_t get_format_tile_size(tile_t *tile, uint32_t *nb_obj,
                                    int nb_player);

bool get_next_tile(char **format_content, tile_t *tile, uint32_t *format_idx,
                    int nb_player)
{
    uint32_t format_size = 0;
    uint32_t nb_obj = 0;

    if (!(format_content) || !(tile))
        return (false);
    format_size = get_format_tile_size(tile, &nb_obj, nb_player);
    if (!(format_size))
        return (true);
    if (!(*format_content =
            realloc(*format_content, format_size + *format_idx)))
        return (false);
    if ((nb_obj || nb_player))
        fill_obj_format(format_content, tile, format_idx, nb_player);
    return (true);
}

v2i_t get_tile_pos(player_t *player, uint32_t dist, int i)
{
    switch (player->dir) {
    case DIR_UP:
        return ((v2i_t){ player->pos.x + i, player->pos.y - dist });
    case DIR_DOWN:
        return ((v2i_t){ player->pos.x - i, player->pos.y + dist });
    case DIR_LEFT:
        return ((v2i_t){ player->pos.x - dist, player->pos.y - i });
    default:
        return ((v2i_t){ player->pos.x + dist, player->pos.y + i });
    }
}

static void fill_obj_format(char **format_content, tile_t *tile,
                            uint32_t *format_idx, int nb_player)
{
    int total_objs = get_total_objs_tile(tile);
    int objs_cpt = 0;

    fill_players(format_content, format_idx, nb_player);
    if (!(total_objs))
        return;
    for (int type = 0; type < OBJ_TOTAL; type++) {
        for (uint32_t obj = 0; obj < tile->objs[type]; obj++) {
            if (nb_player && !(objs_cpt))
                (*format_content)[(*format_idx)++] = ' ';
            for (int i = 0; object_type_names[type][i]; i++)
                (*format_content)[(*format_idx)++] = object_type_names[type][i];
            if (objs_cpt < total_objs - 1)
                (*format_content)[(*format_idx)++] = ' ';
            objs_cpt++;
            }
    }
}

static uint32_t get_format_object_size(object_type_t type)
{
    return (strlen(object_type_names[type]));
}

static uint32_t get_format_tile_size(tile_t *tile, uint32_t *nb_obj,
                                    int nb_player)
{
    uint32_t size = 0;

    if (nb_player) {
        size += (nb_player * 6);
        size += (nb_player - 1);
    }
    for (int i = 0; i < OBJ_TOTAL; i++) {
        if (tile->objs[i]) {
            size += get_format_object_size(i) * tile->objs[i];
            *nb_obj += (tile->objs[i]);
        }
    }
    if (*nb_obj && nb_player)
        size++;
    if (*nb_obj)
        size += ((*nb_obj) - 1);
    return (size);
}