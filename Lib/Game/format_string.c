/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** format_string
*/

#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *format_string(uint32_t *inventory);
static size_t get_size_string(const char **obj_names, uint32_t *inventory);

char *get_formated_inventory(player_t *player)
{
    uint32_t *inventory = NULL;

    if (!player)
        return (NULL);
    if (!(inventory = get_player_inventory(player)))
        return (NULL);
    return (format_string(inventory));
}

static size_t get_size_string(const char **obj_names, uint32_t *inventory)
{
    return (snprintf(NULL, 0,
        "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]",
        obj_names[0], inventory[0], obj_names[1], inventory[1], obj_names[2],
        inventory[2], obj_names[3], inventory[3], obj_names[4], inventory[4],
        obj_names[5], inventory[5], obj_names[6], inventory[6]
    ));
}

static char *format_string(uint32_t *inventory)
{
    static const char *obj_names[7] = {
        "food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"
    };
    char *formated_inventory = NULL;
    size_t size = 0;

    size = get_size_string(obj_names, inventory);
    if (!(formated_inventory = malloc(sizeof(char) * (size + 1))))
        return (NULL);
    sprintf(formated_inventory,
        "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]",
        obj_names[0], inventory[0], obj_names[1], inventory[1], obj_names[2],
        inventory[2], obj_names[3], inventory[3], obj_names[4], inventory[4],
        obj_names[5], inventory[5], obj_names[6], inventory[6]
    );
    formated_inventory[size] = 0;
    return formated_inventory;
}
