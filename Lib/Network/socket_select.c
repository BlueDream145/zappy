/*
** EPITECH PROJECT, 2019
** refonte
** File description:
** socket_select
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"

static const int C_DELAY = 5;

static void set_fdset(socket_t *sock, fdsets_t *fset);
static void set_timeval(struct timeval *tv);
static select_t get_select_res(socket_t *sock, fdsets_t *fset, int res);

select_t select_socket(socket_t *sock)
{
    fdsets_t fset;
    int res;
    struct timeval tv;

    set_fdset(sock, &fset);
    set_timeval(&tv);
    res = select(sock->fd + 1, &fset.rset, &fset.wset, NULL, &tv);
    if (res == SELECT_ERROR)
        perror("Socket select");
    return get_select_res(sock, &fset, res);
}

static void set_fdset(socket_t *sock, fdsets_t *fset)
{
    FD_ZERO(&fset->rset);
    FD_SET(sock->fd, &fset->rset);
    FD_ZERO(&fset->wset);
    FD_SET(sock->fd, &fset->wset);
}

static void set_timeval(struct timeval *tv)
{
    tv->tv_sec = C_DELAY;
    tv->tv_usec = 0;
}

static select_t get_select_res(socket_t *sock, fdsets_t *fset, int res)
{
    if (res < 0)
        return SELECT_ERROR;
    if (!res)
        return SELECT_CLOSE;
    if (FD_ISSET(sock->fd, &fset->rset))
        return SELECT_READ;
    else if (FD_ISSET(sock->fd, &fset->wset))
        return SELECT_WRITE;
    return SELECT_ERROR;
}
