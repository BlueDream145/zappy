/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** socket_stream
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "socket.h"

bool write_socket(socket_t *sock, const char *fmt, ...)
{
    va_list list;
    bool res;

    va_start(list, fmt);
    res = vwrite_socket(sock, fmt, list);
    va_end(list);
    return res;
}

bool vwrite_socket(socket_t *sock, const char *fmt, va_list list)
{
    static char buffer[C_SOCKET_BUFFER];
    ssize_t size = 0;

    memset(buffer, 0, C_SOCKET_BUFFER);
    vsnprintf(buffer, C_SOCKET_BUFFER, fmt, list);
    size = strlen(buffer);
    if (write(sock->fd, buffer, size) != size) {
#ifdef SOCKET_VERBOSE
        fprintf(stderr, "Couldn't write socket (fd: %d)\n", sock->fd);
#endif
        return false;
    }
#ifdef SOCKET_VERBOSE
    fprintf(stderr, "Sent: %s", buffer);
#endif
    return true;
}

bool write_rawdata_socket(socket_t *sock, void *buffer, ssize_t size)
{
    if (write(sock->fd, buffer, size) != size) {
#ifdef SOCKET_VERBOSE
        fprintf(stderr, "Couldn't write socket (fd: %d)\n", sock->fd);
#endif
        return false;
    }
#ifdef SOCKET_VERBOSE
    fprintf(stderr, "Sent raw data socket");
#endif
    return true;
}

bool read_socket(socket_t *sock)
{
    ssize_t size;

    clear_socket_buffer(sock);
    size = read(sock->fd, sock->buffer, C_SOCKET_BUFFER);
    if (size <= 0 || size >= C_SOCKET_BUFFER) {
#ifdef SOCKET_VERBOSE
        //fprintf(stderr, "Couldn't read socket (fd: %d)\n", sock->fd);
#endif
        return false;
    }
#ifdef SOCKET_VERBOSE
    fprintf(stderr, "Received: %s", sock->buffer);
#endif
    return true;
}