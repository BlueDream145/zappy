/*
** EPITECH PROJECT, 2019
** refonte
** File description:
** socket
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "socket.h"

bool init_socket(socket_t *sock)
{
    sock->fd = -1;
    clear_socket_buffer(sock);
    clear_socket_ip(sock);
    sock->port = 0;
    return true;
}

void clear_socket(socket_t *sock)
{
    if (sock->fd != -1)
        close(sock->fd);
    sock->fd = -1;
}

void clear_socket_buffer(socket_t *sock)
{
    memset(sock->buffer, 0, C_SOCKET_BUFFER);
}

void clear_socket_ip(socket_t *sock)
{
    memset(sock->ip, 0, C_BUFFER_ADDR_SIZE);
}