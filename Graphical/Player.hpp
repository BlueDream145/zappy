/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Player
*/

#pragma once

#include "Core/V2.hpp"

struct Player
{
    enum Direction {
        Up = 0,
        Right,
        Down,
        Left
    };

    oA::V2u pos;
    Direction dir = Down;
    bool incanting = false;
};
