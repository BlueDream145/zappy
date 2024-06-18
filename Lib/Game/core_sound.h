/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core_sound
*/

#pragma once

typedef enum {
    SOUND_DIR_CENTER = 0,
    SOUND_DIR_RIGHT,
    SOUND_DIR_UP_RIGHT,
    SOUND_DIR_UP,
    SOUND_DIR_UP_LEFT,
    SOUND_DIR_LEFT,
    SOUND_DIR_DOWN_LEFT,
    SOUND_DIR_DOWN,
    SOUND_DIR_DOWN_RIGHT,
    SOUND_DIR_TOTAL
} sound_direction_t;

typedef struct v2d_s {
    double x;
    double y;
} v2d_t;
