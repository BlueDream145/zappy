/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** tests_socket
*/

#include <criterion/criterion.h>
#include "socket.h"

Test(socket, Basics)
{
    const char *ip = "127.0.0.1";
    const port_t port = 8085;
    socket_t clt, srv, srvTarget;

    cr_assert(init_server_socket(&srv, ip, port, 3));
    cr_assert(init_client_socket(&clt, ip, port));
    srvTarget = accept_socket(&srv);
    cr_assert(write_socket(&srvTarget, "Hello"));
    cr_assert(read_socket(&clt));
    cr_assert_str_eq(clt.buffer, "Hello");
    clear_socket(&clt);
    clear_socket(&srv);
    clear_socket(&srvTarget);
}