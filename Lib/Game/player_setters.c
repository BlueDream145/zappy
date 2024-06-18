/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player_setters
*/

#include "player.h"

void set_player_pos(player_t *player, v2u_t pos)
{
    if (player)
        player->pos = pos;
}

void set_player_dir(player_t *player, dir_t dir)
{
    if (player)
        player->dir = dir;
}

void set_player_object_amount(player_t *player, object_type_t type,
                                uint32_t amount)
{
    if (player) {
        player->inventory[type] = amount;
    }
}

void add_player_object_amount(player_t *player, object_type_t type,
                                uint32_t amount)
{
    if (!(player))
        return;
    set_player_object_amount(player, type,
                            get_player_object_amount(player, type) +
                            amount);
}

void sub_player_object_amount(player_t *player, object_type_t type,
                                uint32_t amount)
{
    if (!(player))
        return;
    set_player_object_amount(player, type,
                            get_player_object_amount(player, type) -
                            amount);
}