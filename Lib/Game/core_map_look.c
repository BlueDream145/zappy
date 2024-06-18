/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core_map_tools
*/

#include <stdio.h>
#include <stdlib.h>
#include "core.h"

static uint32_t get_nb_visible_tile(uint32_t fov);
static int get_nb_player_pos(core_t *core, v2u_t pos);
static bool fill_end_format(char **format, int idx);

char *get_tiles_content(map_t *map, tile_t **tiles, uint32_t nb_tiles,
                        int *players)
{
    uint32_t format_idx = 1;
    char *format_content = malloc(sizeof(char) * 2);

    if (!(map) || !(tiles) || !(format_content) || !(players))
        return (NULL);
    format_content[0] = '[';
    for (uint32_t i = 0; i < nb_tiles; i++) {
        if (!(get_next_tile(&format_content, tiles[i],
                            &format_idx, players[i])))
            return (format_content);
        if (i != nb_tiles - 1 &&
            (format_content = realloc(format_content, format_idx + 1)))
            format_content[format_idx++] = ',';
        if (!(format_content))
            return (NULL);
    }
    if (!(fill_end_format(&format_content, format_idx)))
        return (NULL);
    return (format_content);
}

tile_t **get_visible_tiles(core_t *core, player_t *player, uint32_t *nb_tile,
                            int **players_pos)
{
    uint32_t nb_visible_tile = get_nb_visible_tile(player->level);
    tile_t **tiles = malloc(sizeof(tile_t *) * (nb_visible_tile + 1));
    int *pos = calloc(nb_visible_tile, sizeof(int));
    v2u_t tile_pos;
    int idx = 0;

    if (!(tiles) || !(pos))
        return (NULL);
    *nb_tile = nb_visible_tile;
    for (int dist = 0; dist <= (int)(player->level); dist++) {
        for (int i = -dist; i <= dist; i++) {
            tile_pos = update_pos_border(core->map.size,
                                        get_tile_pos(player, dist, i));
            pos[idx] += get_nb_player_pos(core, tile_pos);
            tiles[idx++] = get_tile(&core->map, tile_pos);
        }
    }
    *players_pos = pos;
    tiles[idx] = NULL;
    return (tiles);
}

static bool fill_end_format(char **format, int idx)
{
    if (!(*format = realloc(*format, idx + 2)))
        return (false);
    (*format)[idx++] = ']';
    (*format)[idx] = 0;
    return (true);
}

static int get_nb_player_pos(core_t *core, v2u_t pos)
{
    int nb_player = 0;

    for (node_t *node = core->players.list.head; node; node = node->next) {
        if (((player_t *)(node->value))->pos.x == pos.x &&
            ((player_t *)(node->value))->pos.y == pos.y)
            nb_player++;
    }
    return (nb_player);
}

static uint32_t get_nb_visible_tile(uint32_t fov)
{
    static uint32_t rate = 3;
    uint32_t nb_tile = 4;

    for (uint32_t i = 1; i < fov; i++) {
        nb_tile += (rate + 2 * i);
    }
    return (nb_tile);
}
