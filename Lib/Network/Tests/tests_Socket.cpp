/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** tests_Socket
*/

#include <criterion/criterion.h>
#include <thread>
#include "Socket.hpp"

Test(Socket, Basics)
{
    net::Socket sock;

    cr_assert_eq(sock.fd(), -1);
}
