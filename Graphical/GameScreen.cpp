/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GameScreen
*/

#include "GameScreen.hpp"

void GameScreen::update(oA::IRenderer &)
{
    auto l = oA::UniqueLock(_m);

    for (const auto &msg : _queue) {
        interpret(msg);
    }
    _queue.clear();
}

void GameScreen::draw(oA::IRenderer &renderer)
{
    drawMap(renderer);
    drawObjects(renderer);
    drawPlayers(renderer);
}

void GameScreen::drawMap(oA::IRenderer &renderer)
{
    oA::ImageContext tile;
    auto x = get("x")->toFloat(), y = get("y")->toFloat();

    tile.source = "Graphical/Resources/grass.jpg";
    tile.size.x = get("width")->toFloat() / _size.x;
    tile.size.y = get("height")->toFloat() / _size.y;
    for (oA::V2u pos; pos.y < _size.y; ++pos.y) {
        for (pos.x = 0; pos.x < _size.x; ++pos.x) {
            tile.pos.x = x + pos.x * tile.size.x;
            tile.pos.y = y + pos.y * tile.size.y;
            renderer.drawImage(tile);
        }
    }
}

void GameScreen::drawObjects(oA::IRenderer &renderer)
{
    oA::ImageContext tile;
    auto x = get("x")->toFloat(), y = get("y")->toFloat();
    oA::V2f size = {
        get("width")->toFloat() / _size.x,
        get("height")->toFloat() / _size.y
    };

    tile.size = size / oA::V2f(3.0f, 3.0f);
    for (auto &obj : _objects) {
        auto delta = obj.getTilePos();
        tile.pos.x = x + size.x * obj.pos.x + tile.size.x * delta.x;
        tile.pos.y = y + size.y * obj.pos.y + tile.size.y * delta.y;
        tile.source = obj.getPath();
        renderer.drawImage(tile);
    }
}

void GameScreen::drawPlayers(oA::IRenderer &renderer)
{
    oA::ImageContext tile;
    auto x = get("x")->toFloat(), y = get("y")->toFloat();

    tile.size.x = get("width")->toFloat() / _size.x;
    tile.size.y = get("height")->toFloat() / _size.y;
    for (auto &player : _players) {
        tile.pos.x = x + player.pos.x * tile.size.x;
        tile.pos.y = y + player.pos.y * tile.size.y;
        tile.source = "Graphical/Resources/player" + oA::ToString(player.dir) + ".png";
        renderer.drawImage(tile);
        if (!player.incanting)
            continue;
        tile.source = "Graphical/Resources/aura.png";
        renderer.drawImage(tile);
    }
}

void GameScreen::connect(void)
{
    try {
        oA::String token;

        _sock.clear();
        _sock.initAsClient(get("ip")->toString(), get("port")->toInt());
        _sock.read(token);
        if (token != "WELCOME\n")
            throw;
        _sock.write("GRAPHIC\n");
        _sock.read(token);
        oA::IStringStream ss(token);
        ss >> _size.x;
        ss >> _size.y;
        if (!_size.x || !_size.y)
            throw;
        _sock.setBlocking(false);
        run();
        get("error") = "";
        get("connected") = true;
    } catch (const std::exception &e) {
        oA::cerr << "Couldn't connect to host @" + get("ip")->toString() + ":"
                    + oA::ToString(get("port")->toInt()) + "@" << oA::endl
                    << "\t-> " << e.what() << oA::endl;
        get("error") = "Couldn't connect to server";
    }
}

void GameScreen::run(void)
{
    stop();
    _running = true;
    _thd = oA::Thread([this] {
        while (_running) {
            oA::String token;
            if (!_sock.read(token)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            _m.lock();
            _queue.emplace_back(token);
            oA::cout << "#Listener thread received:# @" + token + "@" << oA::endl;
            _m.unlock();
        }
    });
}

void GameScreen::stop(void)
{
    if (_running && _thd.joinable()) {
        _running = false;
        _thd.join();
    }
}

void GameScreen::interpret(const oA::String &token)
{
    oA::String type;
    oA::IStringStream ss(token);

    if (!(ss >> type))
        return;
    if (type == "p")
        interpretPlayers(ss);
    else if (type == "o")
        interpretObjects(ss);
    else if (type == "m")
        interpretMessages(ss);
}

void GameScreen::interpretPlayers(oA::IStringStream &ss)
{
    oA::String token;

    _players.clear();
    while (std::getline(ss, token, ';')) {
        oA::IStringStream sub(token);
        auto &p = _players.emplace_back();
        sub >> p.pos.x;
        sub >> p.pos.y;
        oA::Int i = 0;
        sub >> i;
        p.dir = static_cast<Player::Direction>(i);
        sub >> i;
        p.incanting = i;
    }
}

void GameScreen::interpretObjects(oA::IStringStream &ss)
{
    oA::String token;
    oA::V2u pos = { 0, 0 };
    oA::Int type = 0;
    oA::Int amount = 0;

    _objects.clear();
    while (std::getline(ss, token, ';')) {
        oA::IStringStream sub(token);
        oA::Int i = 0;
        sub >> i;
        pos.x = i % (_size.x);
        pos.y = i / (_size.x);
        sub >> type;
        sub >> amount;
        for (oA::Int cpt = 0; cpt < amount; cpt++) {
            auto &obj = _objects.emplace_back();
            obj.type = static_cast<Object::Type>(type);
            obj.pos.x = pos.x;
            obj.pos.y = pos.y;
        }
    }
}

void GameScreen::interpretMessages(oA::IStringStream &ss)
{
    oA::String token;

    std::getline(ss, token);
    if (!token.empty())
        _log.emplace_back(std::move(token));
}
