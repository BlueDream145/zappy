/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** socket_data
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "socket.h"

static bool retrieve_localaddr(socket_t *sock);

bool retrieve_socket_data(socket_t *sock)
{
    struct sockaddr_in in;
    struct sockaddr *pin = (struct sockaddr *)(&in);
    socklen_t size = sizeof(in);

    memset(sock->ip, 0, C_BUFFER_ADDR_SIZE);
    if (getpeername(sock->fd, pin, &size) == -1) {
        perror("Socket retrieve data");
        return false;
    }
    inet_ntop(AF_INET, &in.sin_addr, sock->ip, INET_ADDRSTRLEN);
    sock->port = ntohs(in.sin_port);
    if (!strcmp(sock->ip, "0.0.0.0"))
        return retrieve_localaddr(sock);
    return true;
}

static bool retrieve_localaddr(socket_t *sock)
{
    static char ac[C_SOCKET_BUFFER];
    struct hostent *host;
    struct in_addr localaddr;

    memset(ac, 0, C_SOCKET_BUFFER);
    gethostname(ac, sizeof(ac));
    host = gethostbyname(ac);
    memcpy(&localaddr, *host->h_addr_list, sizeof(localaddr));
    strcpy(sock->ip, inet_ntoa(localaddr));
    return true;
}