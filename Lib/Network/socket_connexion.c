/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** socket_api_connexion
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include "socket.h"

bool bind_socket(socket_t *sock, const char *ip, port_t port)
{
    struct sockaddr_in addr;
    struct sockaddr *p_addr = (struct sockaddr *)(&addr);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip ? inet_addr(ip) : INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(sock->fd, p_addr, sizeof(struct sockaddr_in))) {
        perror("Socket bind");
        return false;
    }
    strcpy(sock->ip, inet_ntoa(addr.sin_addr));
    sock->port = port;
    return true;
}

socket_t accept_socket(socket_t *sock)
{
    struct sockaddr_in addr;
    struct sockaddr *addr_ptr = (struct sockaddr *)(&addr);
    socklen_t size = sizeof(struct sockaddr_in);
    socket_t client;

    init_socket(&client);
    client.fd = accept(sock->fd, addr_ptr, &size);
    if (client.fd == -1)
        perror("Socket accept");
    return client;
}

bool connect_socket(socket_t *sock, const char *ip, port_t port)
{
    struct sockaddr_in addr;
    struct sockaddr *p_addr = (struct sockaddr *)(&addr);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip ? inet_addr(ip) : INADDR_ANY;
    addr.sin_port = htons(port);
    if (connect(sock->fd, p_addr, sizeof(struct sockaddr_in))) {
        perror("Socket connect");
        return false;
    }
    return true;
}