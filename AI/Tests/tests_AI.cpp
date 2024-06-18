/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tests_server
*/

#include <criterion/criterion.h>
#include "AI.hpp"

Test(AI, Basics)
{
    AI::CommandState();
    AI::Server();
}