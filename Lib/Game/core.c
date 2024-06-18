/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core
*/

#include "core.h"

bool init_core(core_t *core, unsigned int map_w, unsigned int map_h)
{
    if (!init_map(&core->map) || !init_player_handler(&core->players))
        return false;
    resize_map(&(core->map), (v2u_t){map_w, map_h});
    init_map_resources(&core->map);
    return true;
}

void clear_core(core_t *core)
{
    clear_map(&core->map);
    clear_player_handler(&core->players);
}