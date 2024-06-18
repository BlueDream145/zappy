/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tests_Player
*/

#include <criterion/criterion.h>
#include "Player.hpp"

Test(Player, Inventory)
{
    Player p;

    p.parseInventory("[]");
    cr_assert_eq(p.getItemCount("lemon"), 0);
    cr_assert_eq(p.getItemCount("apple"), 0);
    cr_assert_eq(p.getItemCount("orange"), 0);
    cr_assert_eq(p.getItemCount("xyz"), 0);
    p.parseInventory("[lemon 3, apple 42, orange 0]");
    cr_assert_eq(p.getItemCount("lemon"), 3);
    cr_assert_eq(p.getItemCount("apple"), 42);
    cr_assert_eq(p.getItemCount("orange"), 0);
}

Test(Player, Look)
{
    Player p;

    p.parseLookCommand("[player,,,thystame linemate,,food,,,,,thystame,,,,,,]");
    cr_assert_eq(p.getLoot()[0].name, "player");
    cr_assert_eq(p.getLoot()[0].position, 0);
    cr_assert_eq(p.getLoot()[1].name, "thystame");
    cr_assert_eq(p.getLoot()[1].position, 3);
    cr_assert_eq(p.getLoot()[2].name, "linemate");
    cr_assert_eq(p.getLoot()[2].position, 3);
    cr_assert_eq(p.getLoot()[3].name, "food");
    cr_assert_eq(p.getLoot()[3].position, 5);
    cr_assert_eq(p.getLoot()[4].name, "thystame");
    cr_assert_eq(p.getLoot()[4].position, 10);
}

Test(Player, filter)
{
    Player p;

    p.parseInventory("[linemate 3, deraumere 2, sibur 0, mendiane 3, phiras 1, thystame 9]");
    cr_assert_eq(p.getItemCount("linemate"), 3);
    cr_assert_eq(p.getItemCount("deraumere"), 2);
    cr_assert_eq(p.getItemCount("sibur"), 0);
    cr_assert_eq(p.getItemCount("mendiane"), 3);
    cr_assert_eq(p.getItemCount("phiras"), 1);
    cr_assert_eq(p.getItemCount("thystame"), 9);
    p.parseLookCommand("[player,,,thystame,,deraumere,,linemate,sibur,mendiane,thystame,,phiras,,,,]");
    cr_assert_eq(p.getLoot()[0].name, "player");
    cr_assert_eq(p.getLoot()[0].position, 0);
}

Test(Player, enough_player_to_elevate)
{
    Player p;

    cr_assert_eq(p.hasEnoughPlayerToElevate(), false);
    p.setLevel(1);
    p.parseLookCommand("[player,,,thystame,,,,,,,,,,,,,]");
    cr_assert_eq(p.hasEnoughPlayerToElevate(), true);
    p.setLevel(2);
    p.parseLookCommand("[player player player player,,,thystame,,,,,,,,,,,,,]");
    cr_assert_eq(p.hasEnoughPlayerToElevate(), true);
    p.setLevel(4);
    p.parseLookCommand("[player player player player,,,thystame,,,,,,,,,,,,,]");
    cr_assert_eq(p.hasEnoughPlayerToElevate(), true);
    p.setLevel(6);
    p.parseLookCommand("[player player player player player player,,,thystame,,,,,,,,,,,,,]");
    cr_assert_eq(p.hasEnoughPlayerToElevate(), true);
}

Test(Player, enough_inventory)
{
    Player p;

    p.parseInventory("[]");
    cr_assert_eq(p.hasItemToElevate(), false);
    p.parseInventory("[linemate 3, deraumere 3, sibur 3, mendiane 3, phiras 3, thystame 3]");
    p.setLevel(1);
    cr_assert_eq(p.hasItemToElevate(), true);
    p.setLevel(2);
    cr_assert_eq(p.hasItemToElevate(), true);
    p.setLevel(3);
    cr_assert_eq(p.hasItemToElevate(), true);
    p.setLevel(4);
    cr_assert_eq(p.hasItemToElevate(), true);
    p.setLevel(5);
    cr_assert_eq(p.hasItemToElevate(), true);
    p.setLevel(6);
    cr_assert_eq(p.hasItemToElevate(), true);
    p.setLevel(7);
    cr_assert_eq(p.hasItemToElevate(), true);
}

Test(Player, notMyMessage)
{
    Player p;

    p.setMessage("K, louis\n");
    p.setName("louis");
    cr_assert_eq(p.notMyMessage(), false);
    p.setName("jack");
    cr_assert_eq(p.notMyMessage(), true);
}

Test(Player, hasToGo)
{
    Player p;

    p.setPosition(2);
    cr_assert_eq(p.hasToGoRight(3), true);
    cr_assert_eq(p.hasToGoRight(1), false);
    cr_assert_eq(p.hasToGoLeft(3), false);
    cr_assert_eq(p.hasToGoLeft(1), true);
    p.setPosition(0);
    cr_assert_eq(p.hasToGoUp(2), true);
    cr_assert_eq(p.hasToGoUp(5), true);
    cr_assert_eq(p.hasToGoUp(12), true);
    cr_assert_eq(p.hasToGoUp(0), false);
}

Test(Player, setter_getter)
{
    Player p;

    cr_assert_eq(p.gotNewMsg(), false);
    cr_assert_eq(p.isAlive(), true);
    p.setName("jack");
    p.setMessage("on est la!");
    p.setWorldSize({2, 4});
    p.setLevel(42);
    p.setPosition(10);
    p.setDirection(RIGHT);
    p.die();
    cr_assert_eq(p.gotNewMsg(), true);
    cr_assert_eq(p.getName(), "jack");
    cr_assert_eq(p.getMessage(), "on est la!");
    cr_assert_eq(p.getLevel(), 42);
    cr_assert_eq(p.getPosition(), 10);
    cr_assert_eq(p.getDirection(), RIGHT);
    cr_assert_eq(p.isAlive(), false);
    cr_assert_eq(p.hasVision(), false);
    p.parseLookCommand("[player,,,thystame linemate,,food,,,,,thystame,,,,,,]");
    p.eraseFirstLoot();
    cr_assert_eq(p.getLoot()[0].name, "thystame");
    cr_assert_eq(p.getLoot()[0].position, 3);
    cr_assert_eq(p.hasVision(), true);
}