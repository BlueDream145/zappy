/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** tests_core
*/

#include <criterion/criterion.h>
#include "core.h"

Test(MapPlayer, LookAround)
{
    core_t core;
    init_core(&core, 10, 10);
    player_t *p = add_player(&core.players);
    init_player(p);
    p->dir = DIR_DOWN;
    p->level = 1;
    p->pos.x = 2;
    p->pos.y = 0;

    add_tile_object(&core.map.data[2], 0);
    cr_assert_str_eq(player_look_around(&core, p), "[player food,,,]");
}

Test(MapPlayer, TakeObject)
{
    core_t core;
    init_core(&core, 10, 10);
    player_t *p = add_player(&core.players);
    init_player(p);
    p->dir = DIR_DOWN;
    p->level = 1;
    p->pos.x = 2;
    p->pos.y = 0;

    add_tile_object(&core.map.data[2], 0);
    get_object_player_map(&core, p, 0);
    cr_assert_str_eq(player_look_around(&core, p), "[player,,,]");
    cr_assert_str_eq(get_formated_inventory(p),
        "[food 1, linemate 0, deraumere 0, sibur 0, "\
        "mendiane 0, phiras 0, thystame 0]");
}

Test(MapPlayer, SetObject)
{
    core_t core;
    init_core(&core, 10, 10);
    player_t *p = add_player(&core.players);
    init_player(p);
    p->dir = DIR_DOWN;
    p->level = 1;
    p->pos.x = 2;
    p->pos.y = 0;

    add_tile_object(&core.map.data[2], 1);

    get_object_player_map(&core, p, 1);
    cr_assert_str_eq(get_formated_inventory(p),
        "[food 0, linemate 1, deraumere 0, sibur 0, "\
        "mendiane 0, phiras 0, thystame 0]");
        set_object_player_map(&core, p, 0);

    set_object_player_map(&core, p, 1);
    cr_assert_str_eq(get_formated_inventory(p),
        "[food 0, linemate 0, deraumere 0, sibur 0, "\
        "mendiane 0, phiras 0, thystame 0]");
        set_object_player_map(&core, p, 0);

    add_tile_object(&core.map.data[12], 0);
    cr_assert_str_eq(player_look_around(&core, p), "[player linemate,,food,]");
}