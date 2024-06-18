/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** socket_helper
*/

#include "socket.h"

bool init_server_socket(socket_t *sock, const char *ip, port_t port, int count)
{
    if (!init_socket(sock) || !open_socket(sock) || !set_socket_opt(sock)
            || !bind_socket(sock, ip, port) || !listen_socket(sock, count))
        return false;
    return true;
}

bool init_client_socket(socket_t *sock, const char *ip, port_t port)
{
    if (!init_socket(sock) || !open_socket(sock)
            || !connect_socket(sock, ip, port))
        return false;
    return true;
}