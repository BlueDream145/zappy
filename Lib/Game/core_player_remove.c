/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core_player_remove
*/

#include "core.h"

bool remove_player_ptr(core_t *core, player_t *player)
{
    if (!player)
        return false;
    remove_node(&(core->players.list), player);
    clear_player(player);
    return true;
}
