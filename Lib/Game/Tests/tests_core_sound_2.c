/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** tests_core
*/

#include <criterion/criterion.h>
#include "core_sound.h"

Test(CoreSound, BasicsDownLeft)
{
    core_t core;
    init_core(&core, 10, 10);
    player_t *p_source = add_player(&core.players);
    player_t *p_dest = add_player(&core.players);
    init_player(p_source);
    init_player(p_dest);
    p_source->pos.x = 1;
    p_source->pos.y = 7;
    p_dest->pos.x = 3;
    p_dest->pos.y = 5;

    cr_assert_eq(get_sound_direction(&core, p_source, p_dest),
                SOUND_DIR_DOWN_LEFT);
}

Test(CoreSound, BasicsUpLeft)
{
    core_t core;
    init_core(&core, 10, 10);
    player_t *p_source = add_player(&core.players);
    player_t *p_dest = add_player(&core.players);
    init_player(p_source);
    init_player(p_dest);
    p_source->pos.x = 1;
    p_source->pos.y = 3;
    p_dest->pos.x = 3;
    p_dest->pos.y = 5;

    cr_assert_eq(get_sound_direction(&core, p_source, p_dest),
                SOUND_DIR_UP_LEFT);
}

Test(CoreSound, BasicsLeft)
{
    core_t core;
    init_core(&core, 10, 10);
    player_t *p_source = add_player(&core.players);
    player_t *p_dest = add_player(&core.players);
    init_player(p_source);
    init_player(p_dest);
    p_source->pos.x = 1;
    p_source->pos.y = 5;
    p_dest->pos.x = 3;
    p_dest->pos.y = 5;

    cr_assert_eq(get_sound_direction(&core, p_source, p_dest),
                SOUND_DIR_LEFT);
}

Test(CoreSound, BasicsDown)
{
    core_t core;
    init_core(&core, 10, 10);
    player_t *p_source = add_player(&core.players);
    player_t *p_dest = add_player(&core.players);
    init_player(p_source);
    init_player(p_dest);
    p_source->pos.x = 3;
    p_source->pos.y = 7;
    p_dest->pos.x = 3;
    p_dest->pos.y = 5;

    cr_assert_eq(get_sound_direction(&core, p_source, p_dest),
                SOUND_DIR_DOWN);
}