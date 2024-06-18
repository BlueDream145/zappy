/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** update
*/

#include "zappy_server.h"

static void check_data_players(zappy_server_t *server, int i)
{
    for (node_t *node = server->graphic_list.head;
        node; node = node->next) {
        zappy_client_t *tmp
            = (zappy_client_t*)(node->value);
        if (tmp->valid && tmp->admin)
            update_data_changed(&tmp->socket,
            &server->gamecore, i);
    }
    server->state[i] = false;
}

void init_super_client(socket_t *sock, core_t *core)
{
    update_items(sock, core);
    update_players(sock, core);
}

void check_data_changed(zappy_server_t *server)
{
    for (int i = 0; i < TotalState; i++)
        if (server->state[i])
            check_data_players(server, i);
}

void update_data_changed(socket_t *sock, core_t *core,
    enum State state)
{
    switch (state) {
        case PlayerChanged:
            update_players(sock, core);
            break;
        case ItemChanged:
            update_items(sock, core);
            break;
        default:
            return;
    }
}
