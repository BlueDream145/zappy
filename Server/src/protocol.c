/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** protocol
*/

#include "zappy_server.h"

static bool is_team_valid(zappy_server_t *server, zappy_client_t *client, \
zappy_team_t *team, char *team_name)
{
    if (!strcmp(team->name, team_name)) {
        if ((unsigned int)team->client_list.size < server->player_nbr) {
            client->valid = true;
            client->admin = false;
            client->team = team;
            client->player = add_player(&(server->gamecore.players));
            init_list(&(client->commands));
            append_list(&(team->client_list), client);
            return (true);
        }
        return (false);
    }
    return (false);
}

static bool add_client_to_team(zappy_server_t *server, \
zappy_client_t *client, char *team_name)
{
    zappy_team_t *team = NULL;

    for (unsigned int i = 0; i != server->team_nbr; i++) {
        team = (zappy_team_t *)at_list(&(server->team_list), i);
        if (is_team_valid(server, client, team, team_name))
            return (true);
    }
    return (false);
}

static bool check_team_name(zappy_server_t *server, zappy_client_t *client)
{
    for (unsigned int i = 0; i != server->team_nbr; i++) {
        if (!strcmp(client->socket.buffer, server->team_name[i])) {
            return (add_client_to_team(server, client, server->team_name[i]));
        }
    }
    return (false);
}

void check_client_command(zappy_server_t *server, zappy_client_t *client)
{
    int len = strlen(client->socket.buffer);

    client->socket.buffer[len - 1] = '\0';
    if (client->valid == false) {
        if (!strcmp(client->socket.buffer, "GRAPHIC")) {
            add_admin_client(server, client);
            send_game_info(server, client);
            server->state[ItemChanged] = true;
            server->state[PlayerChanged] = true;
            return;
        }
        else if (check_team_name(server, client)) {
            send_game_info(server, client);
            return;
        }
        write_socket(&(client->socket), "ko\n");
        return;
    }
    process_command(server, client);
}
