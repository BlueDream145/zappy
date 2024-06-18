/*
** EPITECH PROJECT, 2019
** refonte
** File description:
** socketAPI
*/

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>

//#define SOCKET_VERBOSE

#define C_SOCKET_BUFFER (1024)
#define C_BUFFER_ADDR_SIZE (20)

typedef uint16_t port_t;

typedef struct socket_s {
    int fd;
    char buffer[C_SOCKET_BUFFER];
    char ip[C_BUFFER_ADDR_SIZE];
    port_t port;
} socket_t;

typedef enum {
    SELECT_ERROR = 0,
    SELECT_CLOSE,
    SELECT_READ,
    SELECT_WRITE
} select_t;

typedef struct fdsets_s {
    fd_set rset;
    fd_set wset;
} fdsets_t;

/* Socket initialization */
bool init_socket(socket_t *sock);
void clear_socket(socket_t *sock);
void clear_socket_buffer(socket_t *sock);
void clear_socket_ip(socket_t *sock);

/* Socket Helper */
bool init_server_socket(socket_t *sock, const char *ip, port_t port, int count);
bool init_client_socket(socket_t *sock, const char *ip, port_t port);

/* Socket API */
bool open_socket(socket_t *sock);
bool set_socket_opt(socket_t *sock);
bool listen_socket(socket_t *sock, int count);
void set_socket_blocking(socket_t *sock, bool value);

/* Socket API Connexion */
bool bind_socket(socket_t *sock, const char *ip, port_t port);
socket_t accept_socket(socket_t *sock);
bool connect_socket(socket_t *sock, const char *ip, port_t port);

/* Socket API Select */
select_t select_socket(socket_t *sock);

/* Stream */
bool write_socket(socket_t *sock, const char *fmt, ...);
bool vwrite_socket(socket_t *sock, const char *fmt, va_list list);
bool write_rawdata_socket(socket_t *sock, void *buffer, ssize_t size);
bool read_socket(socket_t *sock);

/* Socket data */
bool retrieve_socket_data(socket_t *sock);