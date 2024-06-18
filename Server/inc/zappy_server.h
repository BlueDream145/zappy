/*
** EPITECH PROJECT, 2019
** server_client
** File description:
** server
*/

#ifndef _ZAPPY_SERVER_H
#define _ZAPPY_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "../../Lib/Game/core.h"
#include "../../Lib/Network/socket.h"
#include "../../Lib/List/list.h"

enum State {
    PlayerChanged = 0,
    ItemChanged,
    IncentationChanged,
    TotalState
};

typedef struct packet_msg_s
{
    int pos;
    int type;
    int amount;
} packet_msg_t;

typedef struct zappy_team_s
{
    char *name;
    list_t client_list;

} zappy_team_t;

typedef struct command_s
{
    char *cmd_cpy;
    char *name;
    char *value;
    unsigned int tick_left;

} command_t;

typedef struct zappy_client_s
{
    bool valid;
    bool admin;
    socket_t socket;
    zappy_team_t *team;
    player_t *player;
    list_t commands;

} zappy_client_t;

typedef struct zappy_server_s
{
    unsigned int map_width;
    unsigned int map_height;
    unsigned int team_nbr;
    char **team_name;
    unsigned int player_nbr;
    int freq;
    socket_t socket;
    list_t client_list;
    list_t team_list;
    fd_set readfds;
    int max_fd;
    struct timeval tv;
    bool state[TotalState];
    bool new_tick;
    core_t gamecore;
    list_t graphic_list;

} zappy_server_t;

/* Server commands */

void reset_fdset(zappy_server_t *server);
bool check_new_connection(zappy_server_t *server);
void check_io_operation(zappy_server_t *server);
void check_client_command(zappy_server_t *server, zappy_client_t *client);
bool zappy_server(zappy_server_t *server);
void handle_sigint(int sig __attribute__((unused)));
bool get_teams_name(char **argv, zappy_server_t *server);
void erase_client(zappy_server_t *server, zappy_client_t *client);
void update_incentation(zappy_server_t *, core_t *);
void check_data_changed(zappy_server_t *server);
void update_data_changed(socket_t *, core_t *, enum State state);
void init_super_client(socket_t *, core_t *);
void update_players(socket_t *, core_t *);
void update_items(socket_t *, core_t *);
char *my_strcat(char *dest, const char *src);
char *my_itc(int nbr);
bool process_ai_command(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exe);
bool init_server(zappy_server_t *server);
bool add_admin_client(zappy_server_t *server, zappy_client_t *client);
void send_game_info(zappy_server_t *server, zappy_client_t *client);
bool process_command(zappy_server_t *server, zappy_client_t *client);
bool check_args(int argc, char **argv, zappy_server_t *server);

/* AI functions from pointers array commands */

bool ai_forward(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);
bool ai_right(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);
bool ai_left(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);
bool ai_look(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);
bool ai_inventory(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);
bool ai_broadcast(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);
bool ai_connect_nbr(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);
bool ai_fork(zappy_server_t *server, zappy_client_t *client, \
command_t *cmd, bool exec);

#endif
