/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core
*/

// NULL
#include <stdlib.h>

#include "core.h"

v2u_t update_pos_border(v2u_t map_size, v2i_t pos)
{
    if (pos.x >= (int)(map_size.x))
        pos.x -= (int)(map_size.x);
    if (pos.y >= (int)(map_size.y))
        pos.y -= (int)(map_size.y);
    if (pos.x < 0)
        pos.x += (int)(map_size.x);
    if (pos.y < 0)
        pos.y += (int)(map_size.y);
    return ((v2u_t){ pos.x, pos.y });
}

char *player_look_around(core_t *core, player_t *player)
{
    tile_t **visible_tiles = NULL;
    uint32_t nb_visible_tile = 0;
    char *tiles_content = NULL;
    int *visible_players = NULL;

    if (!(core) || !(player))
        return (NULL);
    if (!(visible_tiles = get_visible_tiles(core, player, &nb_visible_tile,
                                            &visible_players)))
        return (NULL);
    if (!(tiles_content = get_tiles_content(&core->map, visible_tiles,
                                        nb_visible_tile, visible_players)))
        return (NULL);
    return (tiles_content);
}

void fill_players(char **format_content, uint32_t *format_idx, int nb_player)
{
    static const char *player_str = "player";

    for (int p = 0; p < nb_player; p++) {
        for (int j = 0; player_str[j]; j++)
            (*format_content)[(*format_idx)++] = player_str[j];
        if (p < (nb_player - 1))
            (*format_content)[(*format_idx)++] = ' ';
    }
}
