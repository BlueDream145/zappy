/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player
*/

#pragma once

#include <List/list.h>
#include "player.h"

typedef struct player_handler_s {
    list_t list;
} player_handler_t;

bool init_player_handler(player_handler_t *handler);
void clear_player_handler(player_handler_t *handler);

/* Players list API */
player_t *add_player(player_handler_t *handler);
bool remove_player(player_handler_t *handler, int index);
player_t *get_player(player_handler_t *handler, int index);