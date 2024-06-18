/*
** EPITECH PROJECT, 2019
** server_client
** File description:
** main
*/

#include <signal.h>

#include "zappy_server.h"

static void display_help(char *binary)
{
    printf("\nUSAGE: %s -p port -x width -y "\
    "height -n name1 name2 ... -c clientsNb -f freq\n"\
    "\tport      is the port number\n"\
    "\twidth     is the width of the world\n"\
    "\theight    is the height of the world\n"\
    "\tnameX     is the name of the team X\n"\
    "\tclientsNb is the number of authorized clients per team\n"\
    "\tfreq      is the reciprocal of time unit "\
    "for execution of actions\n\n", binary);
}

int main(int argc, char **argv)
{
    zappy_server_t server;

    signal(SIGINT, handle_sigint);
    memset(&server, 0, sizeof(server));
    if (!check_args(argc, argv, &server)) {
        display_help(argv[0]);
        return (84);
    }
    if (!zappy_server(&server))
        return (84);
    return (0);
}
