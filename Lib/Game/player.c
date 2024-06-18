/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player
*/

// free
#include <stdlib.h>

#include "player.h"

static void init_player_inventory(player_t *player);

bool init_player(player_t *player)
{
    player->pos.x = 0;
    player->pos.y = 0;
    player->dir = DIR_UP;
    player->level = 1;
    player->incentation = false;
    init_player_inventory(player);
    return true;
}

static void init_player_inventory(player_t *player)
{
    if (player) {
        for (int i = 0; i < OBJ_TOTAL; i++)
            player->inventory[i] = 0;
    }
}

void clear_player(player_t *player)
{
    (void)player;
}