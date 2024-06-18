/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** zappy_server
*/

#include "zappy_server.h"

static void reset_timeval(zappy_server_t *server)
{
    double min = 1;
    double freq = server->freq;
    double res = min / freq;

    if (!server->tv.tv_sec && !server->tv.tv_usec) {
        server->new_tick = true;
        server->tv.tv_sec = res;
        server->tv.tv_usec = res * 1000000;
    }
}

static void check_client_command_queue(zappy_server_t *server, \
zappy_client_t *client)
{
    node_t *node = NULL;
    command_t *command = NULL;

    node = client->commands.head;
    while (node) {
        command = (command_t *)node->value;
        if (!command->tick_left) {
            process_ai_command(server, client, command, true);
            remove_node(&(client->commands), command);
            free(command);
            return;
        }
        command->tick_left--;
        node = node->next;
    }
}

static void check_game_state(zappy_server_t *server)
{
    node_t *node = NULL;
    zappy_client_t *client = NULL;
    static uint32_t cpt_resources = 0;

    node = server->client_list.head;
    while (node) {
        client = (zappy_client_t *)node->value;
        if (client->valid && !client->admin)
        check_client_command_queue(server, client);
        node = node->next;
    }
    if (++cpt_resources > 500) {
        server->state[ItemChanged] = true;
        update_map_resources(&(server->gamecore.map));
        cpt_resources = 0;
    }
}

bool zappy_server(zappy_server_t *server)
{
    if (!init_server(server))
        return (false);
    while (true) {
        reset_timeval(server);
        reset_fdset(server);
        if (select(server->max_fd + 1, &(server->readfds), \
        NULL, NULL, &(server->tv)))
            server->new_tick = false;
        if (!check_new_connection(server))
            return (false);
        check_io_operation(server);
        if (server->new_tick)
            check_game_state(server);
        check_data_changed(server);
    }
    return (true);
}
