/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** info_cmd
*/

#include "zappy_server.h"

bool ai_look(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec)
{
    char *response = NULL;

    if (!exec) {
        cmd->tick_left = 7;
        return (append_list(&(client->commands), cmd));
    }
    response = player_look_around(&(server->gamecore), client->player);
    if (response) {
        write_socket(&(client->socket), "%s\n", response);
        printf("[sent]     [%s:%d] %s\n", \
        client->socket.ip, client->socket.port, response);
    }
    return (true);
}

bool ai_inventory(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec)
{
    char *response = NULL;

    if (!exec) {
        cmd->tick_left = 1;
        return (append_list(&(client->commands), cmd));
    }
    response = look_inventory(&(server->gamecore), client->player);
    if (response) {
        write_socket(&(client->socket), "%s\n", response);
        printf("[sent]     [%s:%d] %s\n", \
        client->socket.ip, client->socket.port, response);
    }
    return (true);
}

static void send_message_to_players(zappy_server_t *server, \
zappy_client_t *sender, char *text)
{
    int num = 0;
    node_t *node = NULL;
    zappy_client_t *client = NULL;

    node = server->client_list.head;
    while (node != NULL) {
        client = (zappy_client_t *)node->value;
        if (client != sender && client->valid && !client->admin) {
            num = get_sound_direction(&(server->gamecore), \
            sender->player, client->player);
            write_socket(&(client->socket), "message %d, %s\n", num, text);
        }
        node = node->next;
    }
}

bool ai_broadcast(zappy_server_t *server, \
zappy_client_t *client, command_t *cmd, bool exec)
{
    if (!exec) {
        cmd->tick_left = 7;
        return (append_list(&(client->commands), cmd));
    }
    send_message_to_players(server, client, cmd->value);
    write_socket(&(client->socket), "ok\n");
    return (true);
}
