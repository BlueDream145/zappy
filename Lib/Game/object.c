/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** object
*/

#include "object.h"

bool init_object(object_t *object, object_type_t type)
{
    object->type = type;
    return true;
}

void clear_object(object_t *object)
{
    (void)(object);
}