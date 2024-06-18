/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player_getters
*/

#include "player.h"
#include <stdlib.h>

v2u_t get_player_pos(player_t *player)
{
    return (player->pos);
}

dir_t get_player_dir(player_t *player)
{
    return (player->dir);
}

uint32_t *get_player_inventory(player_t *player)
{
    uint32_t *inventory = malloc(sizeof(uint32_t) * (OBJ_TOTAL));

    if (!inventory || !player)
        return (NULL);
    for (int i = 0; (i < OBJ_TOTAL); i++) {
        inventory[i] = get_player_object_amount(player, i);
    }
    return (inventory);
}

uint32_t get_player_object_amount(player_t *player, object_type_t type)
{
    if (player) {
        return (player->inventory[type]);
    }
    return (0);
}
