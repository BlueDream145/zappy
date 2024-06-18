/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** AI
*/

// std::istringstream
#include <sstream>
// std::regex
#include <regex>
// std::unordered_map
#include <unordered_map>

#include "AI.hpp"

#include <iostream>

void AI::serverHandshake(void)
{
    std::string token;
    V2i size;

    _server.sock.initAsClient(_server.host, _server.port);
    if (!_server.sock.read(token))
        throw std::runtime_error("Server handhsake protocol mismatch");
    _server.sock.write("%s\n", _player.getName().c_str());
    if (!_server.sock.read(token) || !std::stoi(token) || !_server.sock.read(token))
        throw std::logic_error("Can't connect to given team");
    std::istringstream ss(token);
    ss >> size.x; ss >> size.y;
    _player.setWorldSize(size);
    if (!size.x || !size.y)
        throw std::runtime_error("Invalid server map size");
}

void AI::sendActionRequest(void)
{
    static const std::unordered_map<Action, std::string> Actions = {
        { Forward, "Forward" },
        { Left, "Left" },
        { Right, "Right" },
        { Look, "Look" },
        { Inventory, "Inventory" },
        { Broadcast, "Broadcast" },
        { ConnectCount, "Connect_nbr" },
        { Fork, "Fork" },
        { Eject, "Eject" },
        { Take, "Take" },
        { Set, "Set" },
        { Incantation, "Incantation" }
    };
    std::string cmd;
    auto it = Actions.find(_decision.action);

    if (it == Actions.end())
        return;
    cmd = it->second;
    if (!_decision.parameters.empty())
        cmd += ' ' + _decision.parameters;
    _server.sock.write("%s\n", cmd.c_str());
    _decision.sent = true;
}

void AI::listenToServer(void)
{
    static const std::unordered_map<Action, std::regex> Answers = {
        { Forward, std::regex("ok\n") },
        { Left, std::regex("ok\n") },
        { Right, std::regex("ok\n") },
        { Look, std::regex("[[]([a-zA-Z0-9]+(, )?)*[]]\n") },
        { Inventory, std::regex("[[]([a-zA-Z]+ [0-9]+(, )?)*[]]\n") },
        { Broadcast, std::regex("ok\n") },
        { ConnectCount, std::regex("[0-9]+\n") },
        { Fork, std::regex("ok\n") },
        { Eject, std::regex("(ok|ko)\n") },
        { Take, std::regex("(ok|ko)\n") },
        { Set, std::regex("(ok|ko)\n") },
        { Incantation, std::regex("Elevation underway\n") }
    };
    auto it = Answers.find(_decision.action);
    std::string token;

    if (!_server.sock.read(token))
        return;
    if (it != Answers.end() && std::regex_match(token, it->second))
        interpretAnswer(token);
    else
        interpretMessage(token);
}

void AI::interpretAnswer(const std::string &token)
{
    static const std::unordered_map<Action, std::function<void(Player &, const std::string &)>> Process = {
        { Forward, [](Player &, const std::string &) {

        }},
        { Left, [](Player &, const std::string &) {

        }},
        { Right, [](Player &, const std::string &) {

        }},
        { Look, [](Player &player, const std::string &token) {
            player.parseLookCommand(token);
        }},
        { Inventory, [](Player &player, const std::string &token) {
            player.parseInventory(token);
        }},
        { Broadcast, [](Player &, const std::string &) {

        }},
        { ConnectCount, [](Player &, const std::string &) {

        }},
        { Fork, [](Player &, const std::string &) {

        }},
        { Eject, [](Player &, const std::string &) {

        }},
        { Take, [](Player &, const std::string &) {

        }},
        { Set, [](Player &, const std::string &) {

        }},
        { Incantation, [](Player &, const std::string &) {

        }}
    };
    auto it = Process.find(_decision.action);

    if (it == Process.end())
        return;
    it->second(_player, token);
    _decision = CommandState();
}

void AI::interpretMessage(const std::string &token)
{
    static const std::unordered_map<std::string, std::function<void(Player &, const std::string &)>> Messages = {
        { "dead", [](Player &player, const std::string &) {
            player.die();
        }},
        { "Current level: [0-9]+\n", [](Player &player, const std::string &token) {
            auto pos = token.find(':');
            player.setLevel(std::stoi(token.substr(pos + 1)));
        }},
        { "message [0-9]+, .*\n", [](Player &player, const std::string &token) {
            auto pos = token.find(' ');
            player.setMessage(token.substr(pos + 1));
        }},
        { "eject: [0-9]+\n", [](Player &, const std::string &) {

        }}
    };

    if (token == "ko") {
        _decision = CommandState();
        return;
    }
    for (auto m : Messages) {
        if (std::regex_match(token, std::regex(m.first)))
            m.second(_player, token);
    }
}