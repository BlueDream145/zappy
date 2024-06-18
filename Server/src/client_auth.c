/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** command
*/

#include "zappy_server.h"

void send_game_info(zappy_server_t *server, zappy_client_t *client)
{
    if (client->admin == true) {
        write_socket(&(client->socket), "%d %d\n", \
        server->map_width, server->map_height);
        return;
    }
    write_socket(&(client->socket), "%d\n", \
    server->player_nbr - client->team->client_list.size);
    write_socket(&(client->socket), "%d %d\n", \
    server->map_width, server->map_height);
}

bool add_admin_client(zappy_server_t *server, zappy_client_t *client)
{
    client->valid = true;
    client->admin = true;
    client->team = NULL;
    client->player = NULL;
    if (append_list(&(server->graphic_list), client))
        return (false);
    return (true);
}

static command_t *create_command_instance(zappy_client_t *client)
{
    command_t *command = NULL;

    command = malloc(sizeof(command_t));
    if (!command)
        return (NULL);
    memset(command, 0, sizeof(command_t));
    if (!client->socket.buffer[0])
        return (NULL);
    command->cmd_cpy = strdup(client->socket.buffer);
    command->name = strtok(command->cmd_cpy, " ");
    if (client->socket.buffer[strlen(command->name)] != '\0')
        command->value = &(command->name[strlen(command->name) + 1]);
    return (command);
}

bool process_command(zappy_server_t *server, zappy_client_t *client)
{
    command_t *command = NULL;

    if (client->valid && !client->admin) {
        command = create_command_instance(client);
        if (!command)
            return (false);
        if (!process_ai_command(server, client, command, false))
            return (false);
    }
    return (true);
}
