/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** core_sound
*/

#include "core.h"
#include "core_sound.h"
#include "math.h"

static v2i_t get_relative_dest(v2u_t map_size, v2u_t source, v2u_t dest);
static double get_distance(v2i_t first, v2i_t second);
static double get_angle(v2i_t first, v2i_t second);
static sound_direction_t convert_angle_to_dir(double sound_angle);

sound_direction_t get_sound_direction(core_t *core, player_t *source,
                                        player_t *dest)
{
    v2i_t relative_dest = { 0, 0 };
    double sound_angle = 0;

    if (!(core) || !(source) || !(dest))
        return (SOUND_DIR_TOTAL);
    relative_dest = get_relative_dest(core->map.size, source->pos, dest->pos);
    if (relative_dest.x == (int32_t)(source->pos.x) &&
        relative_dest.y == (int32_t)(source->pos.y))
        return (SOUND_DIR_CENTER);
    sound_angle = get_angle((v2i_t){ source->pos.x, source->pos.y },
                            relative_dest);
    return (convert_angle_to_dir(sound_angle));
}

static v2i_t get_relative_dest(v2u_t map_size, v2u_t source, v2u_t dest)
{
    double dist = 30 * 30;
    int idx = 0;
    double actual = 0;
    const v2i_t relative_index[9] = {
        { -map_size.x, - map_size.y }, { 0, -map_size.y },
        { map_size.x, -map_size.y }, { -map_size.x, 0 }, { 0, 0 },
        { map_size.x, 0 }, { -map_size.x, map_size.y }, { 0, map_size.y },
        { map_size.x, map_size.y },
    };

    for (int i = 0; i < 9; i++) {
        actual = get_distance((v2i_t){ source.x, source.y },
                                (v2i_t){ dest.x + relative_index[i].x,
                                        dest.y + relative_index[i].y});
        if (actual <= dist) {
            dist = actual;
            idx = i;
        }
    }
    return ((v2i_t){ relative_index[idx].x + dest.x,
                    relative_index[idx].y + dest.y });
}

static double get_distance(v2i_t first, v2i_t second)
{
    int32_t dx = second.x - first.x;
    int32_t dy = second.y - first.y;

    return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

static double get_angle(v2i_t source, v2i_t dest)
{
    static const double pi = 3.14159265;
    int32_t dx = source.x - dest.x;
    int32_t dy = source.y - dest.y;
    double angle = 0;

    angle = atan2((-dy), (dx)) * (180 / pi) - 22.5;
    if (angle < 0)
        angle += 360;
    return (angle);
}

static sound_direction_t convert_angle_to_dir(double sound_angle)
{
    static const v2d_t angle_directions[SOUND_DIR_TOTAL] = {
        { 400, 400 }, { 315, 360 }, { 0, 45 }, { 45, 90}, { 90, 135 },
        { 135, 180 }, { 180, 225 }, { 225, 270 }, { 270, 315 }
    };

    for (int i = 0; i < SOUND_DIR_TOTAL; i++) {
        if (!(i))
            continue;
        if (sound_angle >= angle_directions[i].x &&
            sound_angle < angle_directions[i].y)
            return ((sound_direction_t)(i));
    }
    return (SOUND_DIR_TOTAL);
}