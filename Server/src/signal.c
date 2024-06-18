/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** signal
*/

#include <stdlib.h>

void handle_sigint(int sig __attribute__((unused)))
{
    exit(0);
}
