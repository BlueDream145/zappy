/*
** EPITECH PROJECT, 2019
** server_client
** File description:
** handle_client
*/

#include "zappy_server.h"

void reset_fdset(zappy_server_t *server)
{
    node_t *node = NULL;

    FD_ZERO(&(server->readfds));
    FD_SET(server->socket.fd, &(server->readfds));
    server->max_fd = server->socket.fd;
    node = server->client_list.head;
    for (int i = 0; node != NULL; i++) {
        zappy_client_t *client = (zappy_client_t *)node->value;
        if (client->socket.fd > 0)
            FD_SET(client->socket.fd, &(server->readfds));
        if (client->socket.fd > server->max_fd)
            server->max_fd = client->socket.fd;
        node = node->next;
    }
}

bool check_new_connection(zappy_server_t *server)
{
    zappy_client_t *client = NULL;

    if (FD_ISSET(server->socket.fd, &(server->readfds))) {
        client = malloc(sizeof(zappy_client_t));
        if (client == NULL)
            return (false);
        memset(client, 0, sizeof(zappy_client_t));
        client->socket = accept_socket(&(server->socket));
        if (client->socket.fd != -1) {
            retrieve_socket_data(&(client->socket));
            printf("[+] New connection from %s:%d\n", \
            client->socket.ip, client->socket.port);
            append_list(&(server->client_list), client);
            write_socket(&(client->socket), "WELCOME\n");
        }
    }
    return (true);
}

void erase_client(zappy_server_t *server, zappy_client_t *client)
{
    printf("[+] Disconnection of %s:%d\n", \
    client->socket.ip, client->socket.port);

    if (client->admin == false && client->valid == true) {
        client->valid = false;
        remove_node(&(client->team->client_list), client);
        remove_player_ptr(&(server->gamecore), client->player);
        free(client->player);
    }
    else if (client->admin && client->valid) {
        remove_node(&(server->graphic_list), client);
    }
    remove_node(&(server->client_list), client);
    close(client->socket.fd);
    free(client);
}

void check_io_operation(zappy_server_t *server)
{
    node_t *node = NULL;

    node = server->client_list.head;
    for (int i = 0; node != NULL; i++) {
        zappy_client_t *client = (zappy_client_t *)node->value;
        if (FD_ISSET(client->socket.fd, &(server->readfds)) && \
        read_socket(&(client->socket)) == 0) {
            erase_client(server, client);
            return;
        }
        else if (FD_ISSET(client->socket.fd, &(server->readfds))) {
            printf("[received] [%s:%d] %s", client->socket.ip, \
            client->socket.port, client->socket.buffer);
            check_client_command(server, client);
        }
        node = node->next;
    }
}
