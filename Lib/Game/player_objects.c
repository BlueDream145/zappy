/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** player_objects
*/

#include "core.h"
#include <stdio.h>

bool get_object_player_map(core_t *core, player_t *player, object_type_t type)
{
    tile_t *player_tile = NULL;

    if (!(core) || !(player))
        return (false);
    if (!(player_tile = get_tile(&core->map, player->pos)))
        return (false);
    if (player_tile->objs[type]) {
        player_tile->objs[type] -= 1;
        add_player_object_amount(player, type, 1);
        return (true);
    }
    return (false);
}

bool set_object_player_map(core_t *core, player_t *player, object_type_t type)
{
    tile_t *player_tile = NULL;

    if (!(core) || !(player))
        return (false);
    if (!(player->inventory[type]))
        return (false);
    if (!(player_tile = get_tile(&core->map, player->pos)))
        return (false);
    player_tile->objs[type] += 1;
    sub_player_object_amount(player, type, 1);
    return (true);
}