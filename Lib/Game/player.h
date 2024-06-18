/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** player
*/

#pragma once

// bool
#include <stdbool.h>
// list_t
#include <List/list.h>

#include "v2u.h"
#include "direction.h"
#include "object.h"

typedef struct player_s {
    v2u_t pos;
    dir_t dir;
    uint32_t inventory[OBJ_TOTAL];
    uint32_t level;
    bool incentation;
} player_t;

bool init_player(player_t *player);
void clear_player(player_t *player);

/* Objects list API */
bool insert_player_object(player_t *player, object_t *object);
object_t *extract_player_object(player_t *player, int index);
object_t *get_player_object(player_t *player, int index);

/* Getters */
v2u_t get_player_pos(player_t *player);
dir_t get_player_dir(player_t *player);
uint32_t *get_player_inventory(player_t *player);
uint32_t get_player_object_amount(player_t *player, object_type_t type);
char *get_formated_inventory(player_t *player);

/* Setters */
void set_player_pos(player_t *player, v2u_t pos);
void set_player_dir(player_t *player, dir_t dir);
void set_player_object_amount(player_t *player, object_type_t type,
                                uint32_t amount);
void add_player_object_amount(player_t *player, object_type_t type,
                                uint32_t amount);
void sub_player_object_amount(player_t *player, object_type_t type,
                                uint32_t amount);