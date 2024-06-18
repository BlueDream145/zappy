/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player_handler
*/

#include "player_handler.h"

bool init_player_handler(player_handler_t *handler)
{
    if (!init_list(&handler->list))
        return false;
    return true;
}

void clear_player_handler(player_handler_t *handler)
{
    while (remove_player(handler, 0));
}