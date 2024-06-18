/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core
*/

#pragma once

#include "player_handler.h"
#include "map.h"
#include "v2i.h"
#include "v2u.h"
#include "core_sound.h"

/* core_t
    players : handler of game players
    map : map of the game
*/
typedef struct core_s {
    player_handler_t players;
    map_t map;
} core_t;

bool init_core(core_t *core, unsigned int map_w, unsigned int map_h);
void clear_core(core_t *core);

/* Player Core API */
tile_t *get_player_tile(core_t *core, player_t *player);
bool remove_player_ptr(core_t *core, player_t *player);

/* Player moves */
void player_move_forward(core_t *core, player_t *player);
void player_turn_left(core_t *core, player_t *player);
void player_turn_right(core_t *core, player_t *player);

/* Player looks */
char *look_inventory(core_t *core, player_t *player);
char *player_look_around(core_t *core, player_t *player);

/* Tools */
v2u_t update_pos_border(v2u_t map_size, v2i_t pos);
tile_t **get_visible_tiles(core_t *core, player_t *player, uint32_t *nb_tile,
                            int **players_pos);
void fill_players(char **format_content, uint32_t *format_idx, int nb_player);
char *get_tiles_content(map_t *map, tile_t **tiles, uint32_t nb_tiles,
                        int *players);
v2i_t get_tile_pos(player_t *player, uint32_t dist, int i);
bool get_next_tile(char **format_content, tile_t *tile, uint32_t *format_idx,
                    int nb_player);
v2i_t *get_visible_players(core_t *core, tile_t **tiles);

/* Elevation */
bool start_incantation(core_t *core, player_t *player);
bool can_start_incantation(core_t *core, player_t *player);
void stop_incentation(core_t *core, player_t *player);

/* Object take/set */
bool get_object_player_map(core_t *core, player_t *player,
                            object_type_t type);
bool set_object_player_map(core_t *core, player_t *player,
                            object_type_t type);

/* Sounds */
sound_direction_t get_sound_direction(core_t *core, player_t *source,
                                        player_t *dest);

/* Resources handling */
void init_map_resources(map_t *map);
void update_map_resources(map_t *map);
