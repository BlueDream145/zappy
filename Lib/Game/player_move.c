/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player_move
*/

#include "player.h"
#include "v2i.h"

void move_player_forward(player_t *player)
{
    static const v2i_t moves[4] = {
        { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 }
    };
    v2u_t new_pos;
    v2u_t actual_pos;
    v2i_t move;

    if (!player)
        return;
    move = moves[player->dir];
    actual_pos = get_player_pos(player);
    new_pos.x = actual_pos.x + move.x;
    new_pos.y = actual_pos.y + move.y;
    set_player_pos(player, new_pos);
}

void turn_player_left(player_t *player)
{
    dir_t actual_dir;

    if (!player)
        return;
    actual_dir = player->dir;
    player->dir = (player->dir == DIR_UP) ? DIR_LEFT : actual_dir - 1;
}

void turn_player_right(player_t *player)
{
    dir_t actual_dir;

    if (!player)
        return;
    actual_dir = player->dir;
    player->dir = (player->dir == DIR_LEFT) ? DIR_UP : actual_dir + 1;
}
