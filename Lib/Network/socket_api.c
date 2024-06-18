/*
** EPITECH PROJECT, 2019
** refonte
** File description:
** socket_api
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>

#include "socket.h"

static const int C_OPT_FLAGS = SO_REUSEADDR | SO_REUSEPORT;

bool open_socket(socket_t *sock)
{
    struct protoent *pe;

    pe = getprotobyname("TCP");
    sock->fd = socket(AF_INET, SOCK_STREAM, pe ? pe->p_proto : 0);
    if (sock->fd == -1) {
        perror("Socket open");
        return false;
    }
    return true;
}

bool set_socket_opt(socket_t *sock)
{
    int opt = 1;

    if (setsockopt(sock->fd, SOL_SOCKET, C_OPT_FLAGS, &opt, sizeof(opt))) {
        perror("Socket set OPT");
        return false;
    }
    return true;
}

bool listen_socket(socket_t *sock, int count)
{
    if (listen(sock->fd, count) == -1) {
        perror("Socket listen");
        return false;
    }
    return true;
}

void set_socket_blocking(socket_t *sock, bool value)
{
    int flags = fcntl(sock->fd, F_GETFL);

    if (value)
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;
    fcntl(sock->fd, F_SETFL, flags);
}