/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player_handler
*/

#include <stdlib.h>
#include "player_handler.h"

player_t *add_player(player_handler_t *handler)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player || !init_player(player))
        return NULL;
    if (!append_list(&handler->list, player)) {
        free(player);
        player = NULL;
    }
    return player;
}

bool remove_player(player_handler_t *handler, int index)
{
    player_t *player = erase_list(&handler->list, index);

    if (!player)
        return false;
    clear_player(player);
    return true;
}

player_t *get_player(player_handler_t *handler, int index)
{
    return at_list(&handler->list, index);
}