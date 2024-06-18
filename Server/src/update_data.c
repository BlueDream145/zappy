/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** update
*/

#include "zappy_server.h"

static char *writeItems(char **buffer, packet_msg_t msg)
{
    *buffer = strcat(*buffer, my_itc(msg.pos));
    *buffer = strcat(*buffer, " ");
    *buffer = strcat(*buffer, my_itc(msg.type));
    *buffer = strcat(*buffer, " ");
    *buffer = strcat(*buffer, my_itc(msg.amount));
    return (*buffer);
}

static void update_item_process(core_t *core, uint32_t pos,
    bool first, char *buffer)
{
    tile_t *tile = get_tile(&core->map, (v2u_t){ pos % core->map.size.x,
        pos / core->map.size.x });
    u_int32_t *tmp = core->map.data[pos].objs;

    for (int i = 0; i < OBJ_TOTAL; i++) {
        if (!tmp[i])
            continue;
        if (!first)
            buffer = strcat(buffer, ";");
        else
            first = false;
        writeItems(&buffer, (packet_msg_t){ pos, i, tmp[i] });
    }
    (void)tile;
}

void update_items(socket_t *sock, core_t *core)
{
    char *buffer = malloc(sizeof(char) * 100000);
    bool first = true;

    buffer[0] = 'o';
    buffer[1] = ' ';
    buffer[2] = 0;
    for (uint32_t pos = 0; pos <
        (core->map.size.x * core->map.size.y); pos++)
        update_item_process(core, pos, first, buffer);
    buffer = strcat(buffer, "\n");
    write_rawdata_socket(sock, buffer, strlen(buffer));
    free(buffer);
}

static char *write_players(char *buffer, player_t *tmp)
{
    buffer = strcat(buffer, my_itc(tmp->pos.x));
    buffer = strcat(buffer, " ");
    buffer = strcat(buffer, my_itc(tmp->pos.y));
    buffer = strcat(buffer, " ");
    buffer = strcat(buffer, my_itc(tmp->dir));
    buffer = strcat(buffer, " ");
    buffer = strcat(buffer, my_itc(tmp->incentation));
    return (buffer);
}

void update_players(socket_t *sock, core_t *core)
{
    char *buffer = malloc(sizeof(char) * 4096);
    player_t *tmp = NULL;
    bool first = true;

    buffer[0] = 'p';
    buffer[1] = ' ';
    buffer[2] = 0;
    for (node_t *node = core->players.list.head;
        node; node = node->next) {
        tmp = (player_t*)(node->value);
        if (!first)
            buffer = strcat(buffer, ";");
        else
            first = false;
        buffer = write_players(buffer, tmp);
    }
    buffer = strcat(buffer, "\n");
    write_rawdata_socket(sock, buffer, sizeof(buffer));
    free(buffer);
}