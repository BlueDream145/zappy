/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core
*/

#include "core.h"
#include "v2i.h"

tile_t *get_player_tile(core_t *core, player_t *player)
{
    return get_tile(&core->map, player->pos);
}

void player_move_forward(core_t *core, player_t *player)
{
    static const v2i_t moves[4] = {
        { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 }
    };
    v2i_t new_pos;
    v2u_t actual_pos;
    v2i_t move;

    if (!player)
        return;
    move = moves[player->dir];
    actual_pos = get_player_pos(player);
    new_pos.x = actual_pos.x + move.x;
    new_pos.y = actual_pos.y + move.y;
    set_player_pos(player, update_pos_border(core->map.size, new_pos));
}

void player_turn_left(core_t *core, player_t *player)
{
    dir_t actual_dir;

    if (!(core) || !(player))
        return;
    actual_dir = player->dir;
    player->dir = (player->dir == DIR_UP) ? DIR_LEFT : actual_dir - 1;
}

void player_turn_right(core_t *core, player_t *player)
{
    dir_t actual_dir;

    if (!(core) || !(player))
        return;
    actual_dir = player->dir;
    player->dir = (player->dir == DIR_LEFT) ? DIR_UP : actual_dir + 1;
}

char *look_inventory(core_t *core, player_t *player)
{
    (void)core;
    return (get_formated_inventory(player));
}