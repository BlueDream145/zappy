/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** elevation
*/

#include "core.h"
#include "elevation_table.h"
#include <stdio.h>

static bool can_elevate_at(core_t *core, player_t *player);
static int get_nb_player_pos_level(core_t *core, v2u_t pos, uint32_t level);

bool start_incantation(core_t *core, player_t *player)
{
    if (!(can_start_incantation(core, player)))
        return (false);
    for (int i = 0; i < OBJ_TOTAL; i++) {
        set_player_object_amount(player, i,
                                get_player_object_amount(player, i) -
                                elevation_table[player->level - 1][i]);
    }
    player->incentation = true;
    return (true);
}

void stop_incentation(core_t *core, player_t *player)
{
    (void)core;
    if (player) {
        player->incentation = false;
        player->level++;
    }
}

bool can_start_incantation(core_t *core, player_t *player)
{
    if (!(core) || !(player))
        return (false);
    return (can_elevate_at(core, player));
}

static int get_nb_player_pos_level(core_t *core, v2u_t pos, uint32_t level)
{
    int nb_player = 0;

    for (node_t *node = core->players.list.head; node; node = node->next) {
        if (((player_t *)(node->value))->pos.x == pos.x &&
            ((player_t *)(node->value))->pos.y == pos.y &&
            ((player_t *)(node->value))->level >= level)
            nb_player++;
    }
    return (nb_player);
}



static bool can_elevate_at(core_t *core, player_t *player)
{
    if (!(player))
        return (false);
    for (int i = 0; i < OBJ_TOTAL; i++) {
        if (player->inventory[i] < elevation_table[player->level - 1][i])
            return (false);
    }
    if (get_nb_player_pos_level(core, player->pos, player->level) ==
        new_player_elevation_table[player->level - 1])
        return (true);
    return (true);
}