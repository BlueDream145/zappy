/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** AI
*/

#pragma once

// Socket
#include "Network/Socket.hpp"

#include "Player.hpp"

/**
 * @brief API of the bot
 *
 * This class establish a connexion to a remote server,
 * then it'll interpret updates and send decisions made using the Player state
 */
class AI
{
public:
    struct Server
    {
        net::Socket sock;
        std::string host = "localhost";
        port_t port = 0;
    };

    struct CommandState
    {
        Action action = NoneAction;
        std::string parameters;
        bool sent = false;
    };

    AI(int ac, const char *av[]);

    void run(void);

private:
    Server _server;
    Player _player;
    CommandState _decision;
    bool _running = false;

    void parseArguments(int ac, const char *av[]);
    void update(void);

    /* AI Decision */
    void takeDecision(void);
    void checkLoot(void);
    void makePlayerGoUp(void);
    void makePlayerGoRight(void);
    void makePlayerGoLeft(void);
    void lookForPlayer(void);

    /* AI Server */
    void serverHandshake(void);
    void sendActionRequest(void);
    void listenToServer(void);
    void interpretAnswer(const std::string &token);
    void interpretMessage(const std::string &token);
};
