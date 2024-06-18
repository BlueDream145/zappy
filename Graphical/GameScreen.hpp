/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GameScreen
*/

#pragma once

#include "Core/Thread.hpp"
#include "Core/Mutex.hpp"
#include "Core/StringStream.hpp"
#include "Core/Vector.hpp"
#include "App/Item.hpp"
#include "Network/Socket.hpp"
#include "Player.hpp"
#include "Object.hpp"

class GameScreen : public oA::Item
{
public:
    GameScreen(void) {
        append("ip") = "";
        append("port") = 0;
        append("connected") = false;
        append("error") = "";
        append("tryConnect").connect([this] { connect(); return true; });
        append("disconnect").connect([this] { _sock.clear(); get("connected") = false; return true; });
    }

    virtual ~GameScreen(void) { stop(); }

    virtual oA::String getName(void) const noexcept { return "GameScreen"; }

    virtual void update(oA::IRenderer &renderer);

    virtual void draw(oA::IRenderer &renderer);
    virtual void drawMap(oA::IRenderer &renderer);
    virtual void drawObjects(oA::IRenderer &renderer);
    virtual void drawPlayers(oA::IRenderer &renderer);

    void connect(void);
    void run(void);
    void stop(void);

    void interpret(const oA::String &token);
    void interpretPlayers(oA::IStringStream &ss);
    void interpretObjects(oA::IStringStream &ss);
    void interpretMessages(oA::IStringStream &ss);

private:
    oA::V2u _size = oA::V2u(10, 10);
    oA::Vector<Player> _players;
    oA::Vector<Object> _objects;
    oA::Vector<oA::String> _queue;
    oA::Vector<oA::String> _log;
    net::Socket _sock;
    oA::Thread _thd;
    oA::Mutex _m;
    bool _running = false;
};