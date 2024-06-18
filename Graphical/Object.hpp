/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Object
*/

#pragma once

#include "Core/V2.hpp"
#include "Core/String.hpp"

struct Object
{
    enum Type {
        Food = 0,
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame
    };

    oA::V2u pos;
    Type type = Food;

    oA::String getPath(void) const noexcept {
        switch (type) {
        case Food:
            return "Graphical/Resources/food.png";
        case Linemate:
            return "Graphical/Resources/red.png";
        case Deraumere:
            return "Graphical/Resources/green.png";
        case Sibur:
            return "Graphical/Resources/blue.png";
        case Mendiane:
            return "Graphical/Resources/cyan.png";
        case Phiras:
            return "Graphical/Resources/magenta.png";
        case Thystame:
            return "Graphical/Resources/yellow.png";
        default:
            return "";
        }
    }

    oA::V2u getTilePos(void) const noexcept {
        switch (type) {
        case Linemate:
            return oA::V2u(0, 0);
        case Deraumere:
            return oA::V2u(1, 0);
        case Sibur:
            return oA::V2u(2, 0);
        case Mendiane:
            return oA::V2u(0, 1);
        case Phiras:
            return oA::V2u(1, 1);
        case Thystame:
            return oA::V2u(2, 1);
        case Food:
            return oA::V2u(1, 2);
        default:
            return oA::V2u();
        }
    }
};
