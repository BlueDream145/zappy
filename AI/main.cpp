/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/


// std::cout
#include <iostream>
// std::string
#include <string>

#include "AI.hpp"

static constexpr auto C_USAGE = \
"USAGE: ./zappy_ai -p port -n name -h machine\n\
\tport is the port number\n\
\tname is the name of the team\n\
\tmachine is the name of the machine; localhost by default";

static void showUsage(void)
{
    std::cout << C_USAGE << std::endl;
}

int main(int ac, const char *av[])
{
    if (ac == 2 && std::string(av[1]) == "-help")
        return showUsage(), 0;
    try {
        AI bot(ac, av);

        bot.run();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}

// socket_t client;

// if (!init_client_socket(&client, "127.0.0.1", 8081)
//         || !read_socket(&client))
//     return 84;
// std::cout << "Client received '" << client.buffer << "'" << std::endl;