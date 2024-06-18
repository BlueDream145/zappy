/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** init_server
*/

#include "zappy_server.h"

static bool init_server_team(zappy_server_t *server)
{
    zappy_team_t *team = NULL;

    for (unsigned int i = 0; i != server->team_nbr; i++) {
        team = malloc(sizeof(zappy_team_t));
        memset(team, 0, sizeof(zappy_team_t));
        if (team == NULL) {
            perror("malloc failled");
            return (false);
        }
        team->name = server->team_name[i];
        init_list(&(team->client_list));
        append_list(&(server->team_list), team);
    }
    return (true);
}

static bool init_zappy_server(zappy_server_t *server)
{
    server->socket.port = (server->socket.port) ?: 4242;
    server->map_width = (server->map_width) ?: 10;
    server->map_height = (server->map_height) ?: 10;
    if (server->team_nbr <= 0) {
        server->team_nbr = 2;
        get_teams_name((char *[4]){"-n", "Team1", "Team2", NULL}, server);
    }
    server->player_nbr = (server->player_nbr) ?: 3;
    server->freq = (server->freq) ?: 100;
    if (!init_server_team(server)) {
        fprintf(stderr, "Cannot init server team\n");
        return (false);
    }
    init_list(&(server->client_list));
    init_list(&(server->graphic_list));
    if (!init_server_socket(&(server->socket), NULL, server->socket.port, 1)) {
        fprintf(stderr, "Cannot init server socket\n");
        return (false);
    }
    return (true);
}

bool init_server(zappy_server_t *server)
{
    if (!init_zappy_server(server))
        return (false);
    if (!init_core(&(server->gamecore), server->map_width, server->map_height))
        return (false);
    if (!listen_socket(&(server->socket), 10))
        return (false);
    printf("[+] Zappy server is listening on %s:%d\n", \
    server->socket.ip, server->socket.port);
    return (true);
}
