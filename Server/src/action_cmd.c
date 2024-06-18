/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** action_cmd
*/

#include "zappy_server.h"

bool ai_forward(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec)
{
    if (!exec) {
        cmd->tick_left = 7;
        return (append_list(&(client->commands), cmd));
    }
    player_move_forward(&(server->gamecore), client->player);
    write_socket(&(client->socket), "ok\n");
    server->state[PlayerChanged] = true;
    printf("[sent]     [%s:%d] %s\n", \
    client->socket.ip, client->socket.port, "ok");
    return (true);
}

bool ai_right(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec)
{
    if (!exec) {
        cmd->tick_left = 7;
        return (append_list(&(client->commands), cmd));
    }
    player_turn_right(&(server->gamecore), client->player);
    write_socket(&(client->socket), "ok\n");
    server->state[PlayerChanged] = true;
    printf("[sent]     [%s:%d] %s\n", \
    client->socket.ip, client->socket.port, "ok");
    return (true);
}

bool ai_left(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec)
{
    if (!exec) {
        cmd->tick_left = 7;
        return (append_list(&(client->commands), cmd));
    }
    player_turn_left(&(server->gamecore), client->player);
    write_socket(&(client->socket), "ok\n");
    server->state[PlayerChanged] = true;
    printf("[sent]     [%s:%d] %s\n", \
    client->socket.ip, client->socket.port, "ok");
    return (true);
}
