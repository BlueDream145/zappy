/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** AI
*/

// std::string
#include <string>

#include <iostream>

#include "AI.hpp"

AI::AI(int ac, const char *av[])
{
    parseArguments(ac, av);
    serverHandshake();
}

void AI::run(void)
{
    _running = true;
    while (_running) {
        update();
    }
}

void AI::parseArguments(int ac, const char *av[])
{
    std::string token, next;
    //int port = 0;

    for (auto i = 1; i < ac - 1; i += 2) {
        token = av[i];
        next = av[i + 1];
        if (token == "-p")
            _server.port = std::stoi(next);
        else if (token == "-n")
            _player.setName(next);
        else if (token == "-h")
            _server.host = next;
    }
    if (!_server.port || _player.getName().empty())
        throw std::logic_error("Missing argument, './zappy_ai -help' for usage");
}

void AI::update(void)
{
    if (!_decision.action)
        takeDecision();
    if (!_decision.sent)
        sendActionRequest();
    listenToServer();
}