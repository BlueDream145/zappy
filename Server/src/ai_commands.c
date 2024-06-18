/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** ai_commands
*/

#include "zappy_server.h"

bool ai_connect_nbr(zappy_server_t *server __attribute__((unused)), \
zappy_client_t *client, command_t *cmd __attribute__((unused)), \
bool exec __attribute__((unused)))
{
    int slot_remaining = 0;

    slot_remaining = server->player_nbr - client->team->client_list.size;
    write_socket(&(client->socket), "%d\n", slot_remaining);
    return (true);
}

bool ai_fork(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec)
{
    if (!exec) {
        cmd->tick_left = 42;
        return (append_list(&(client->commands), cmd));
    }
    (void)server;
    write_socket(&(client->socket), "ok\n");
    return (true);
}

bool process_ai_command(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exe)
{
    int ret = 0;
    const char *ai_cmd[9] = {"Forward", "Right", "Left", "Look", \
    "Inventory", "Broadcast", "Connect_nbr", "Fork", NULL};
    bool (*cmds[9])(zappy_server_t *server, zappy_client_t *client, \
    command_t *cmd, bool exec) = {&ai_forward, &ai_right, &ai_left, \
    &ai_look, &ai_inventory, &ai_broadcast, &ai_connect_nbr, &ai_fork, NULL};

    if (!cmd)
        return (false);
    for (int i = 0; ai_cmd[i] != NULL; i++) {
        if (!strcasecmp(ai_cmd[i], cmd->name)) {
            ret = (*cmds[i])(server, client, cmd, exe);
            return (ret);
        }
    }
    return (true);
}
