/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** check_args
*/

#include <getopt.h>

#include "zappy_server.h"

bool get_teams_name(char **argv, zappy_server_t *server)
{
    int i = 0;
    int j = 0;

    while (strcmp(argv[i], "-n") != 0)
        i++;
    i++;
    while (argv[i] != NULL && argv[i][0] != '-') {
        server->team_nbr++;
        i++;
    }
    server->team_name = malloc(sizeof(char *) * (server->team_nbr + 1));
    if (server->team_name == NULL)
        return (false);
    i -= server->team_nbr;
    for (j = 0; j != (int)server->team_nbr; j++, i++)
        server->team_name[j] = strdup(argv[i]);
    server->team_name[j] = NULL;
    return (true);
}

static bool check_value(int opt, int value)
{
    if (opt == 'x' || opt == 'y') {
        if (value < 10 || value > 30) {
            printf("\n-%c option only accepts integer values "\
            "between 10 and 30\n", opt);
            return (false);
        }
    }
    else if (opt == 'f') {
        if (value < 2 || value > 10000) {
            printf("\n-f option only accepts integer "\
            "values between 2 and 10000\n");
            return (false);
        }
    }
    return (true);
}

static bool check_option(int opt, zappy_server_t *server, char **argv)
{
    if (opt == 'p' && optarg[0] != '-')
        server->socket.port = atoi(optarg);
    if (opt == 'x' && optarg[0] != '-') {
        server->map_width = atoi(optarg);
        return (check_value(opt, server->map_width));
    }
    if (opt == 'y' && optarg[0] != '-') {
        server->map_height = atoi(optarg);
        return (check_value(opt, server->map_height));
    }
    if (opt == 'n' && optarg[0] != '-') {
        if (!get_teams_name(argv, server))
            return (false);
    }
    if (opt == 'c' && optarg[0] != '-')
        server->player_nbr = atoi(optarg);
    if (opt == 'f' && optarg[0] != '-') {
        server->freq = atoi(optarg);
        return (check_value(opt, server->freq));
    }
    return (true);
}

bool check_args(int argc, char **argv, zappy_server_t *server)
{
    int opt;

    opterr = 0;
    while ((opt = getopt(argc, argv, "p:x:y:n:c:f:")) != -1) {
        if (opt == '?')
            return (false);
        if (!check_option(opt, server, argv))
            return (false);
    }
    return (true);
}
