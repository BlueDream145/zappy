/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** elevation_table
*/

#pragma once

#include "object.h"

static const uint32_t elevation_table[OBJ_TOTAL][7] = {
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 0, 0, 0 },
    { 0, 2, 0, 1, 0, 2, 0 },
    { 0, 1, 1, 2, 0, 1, 0 },
    { 0, 1, 2, 1, 3, 0, 0 },
    { 0, 1, 2, 3, 0, 1, 0 },
    { 0, 2, 2, 2, 2, 2, 1 }
};

static const int new_player_elevation_table[7] = {
    0,
    1,
    0,
    1,
    0,
    1,
    0,
};
