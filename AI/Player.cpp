/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Player
*/

// std::istringstream
#include <sstream>

#include "Player.hpp"

unsigned int Player::getItemCount(const std::string &name)
{
    auto it = _inventory.find(name);

    if (it == _inventory.end())
        return 0;
    return it->second;
}

void Player::setItemCount(const std::string &name, unsigned int count)
{
    _inventory[name] = count;
}

void Player::parseInventory(const std::string &inventory)
{
    std::istringstream ss(inventory);
    std::string name;
    unsigned int count = 0;
    char c = 0;

    for (ss.read(&c, 1); ss.good(); ss.read(&c, 1)) {
        if (c == ',' || c == '[' || c == ']')
            continue;
        if (c != ' ') {
            ss >> name;
            name.insert(0, 1, c);
        } else if (name.empty())
            continue;
        ss >> count;
        setItemCount(name, count);
        name.clear();
        count = 0;
    }
}

void Player::parseLookCommand(const std::string &look)
{
    int position = 0;
    std::string token;
    Object tmp;

    _loot.clear();
    for (auto it = look.begin(); it != look.end(); it++) {
        if (*it == '[' || *it == ']')
            continue;
        if (*it == ',') {
            tmp.name.assign(token);
            tmp.position = position;
            if (!tmp.name.empty())
                _loot.push_back(tmp);
            token.clear();
            position++;
            continue;
        }
        if (*it == ' ') {
            tmp.name.assign(token);
            tmp.position = position;
            _loot.push_back(tmp);
            token.clear();
            continue;
        }
        token.insert(token.end(), *it);
    }
    filterLoot();
}

void Player::filterLoot(void)
{
    auto loot = _loot;

    _loot.clear();
    for (const auto &object : loot) {
        if (object.name == "player" || object.name == "food")
            _loot.push_back(object);
        if (object.name == "linemate" && getItemCount("linemate") < 9)
            _loot.push_back(object);
        if (object.name == "deraumere" && getItemCount("deraumere") < 8)
            _loot.push_back(object);
        if (object.name == "sibur" && getItemCount("sibur") < 10)
            _loot.push_back(object);
        if (object.name == "mendiane" && getItemCount("mendiane") < 5)
            _loot.push_back(object);
        if (object.name == "phiras" && getItemCount("phiras") < 6)
            _loot.push_back(object);
        if (object.name == "thystame" && getItemCount("thystame") < 1)
            _loot.push_back(object);
    }
}

bool Player::hasToGoUp(unsigned int pos) const
{
    if (pos >= 1 && pos <= 3 && position < 1)
        return true;
    if (pos >= 4 && pos <= 8 && position < 4)
        return true;
    if (pos >= 9 && pos <= 15 && position < 9)
        return true;
    return false;
}

bool Player::hasToGoRight(unsigned int pos) const
{
    if (position < pos)
        return true;
    return false;
}

bool Player::hasToGoLeft(unsigned int pos) const
{
    if (position > pos)
        return true;
    return false;
}

bool Player::hasItemToElevate()
{
    if (_level == 1 && getItemCount("linemate") >= 1)
        return true;
    if (_level == 2 && getItemCount("linemate") >= 1 && getItemCount("deraumere") >= 1 && getItemCount("sibur") >= 1)
        return true;
    if (_level == 3 && getItemCount("linemate") >= 2 && getItemCount("sibur") >= 1 && getItemCount("phiras") >= 2)
        return true;
    if (_level == 4 && getItemCount("linemate") >= 1 && getItemCount("deraumere") >= 1 && getItemCount("sibur") >= 2 && getItemCount("phiras") >= 1)
        return true;
    if (_level == 5 && getItemCount("linemate") >= 1 && getItemCount("deraumere") >= 2 && getItemCount("sibur") >= 1 && getItemCount("mendiane") >= 3)
        return true;
    if (_level == 6 && getItemCount("linemate") >= 1 && getItemCount("deraumere") >= 2 && getItemCount("sibur") >= 3 && getItemCount("phiras") >= 1)
        return true;
    if (_level == 7 && getItemCount("linemate") >= 2 && getItemCount("deraumere") >= 2 && getItemCount("sibur") >= 2 && getItemCount("mendiane") >= 2 && getItemCount("phiras") >= 2 && getItemCount("thystame") >= 1)
        return true;
    return false;
}

bool Player::hasEnoughPlayerToElevate()
{
    int nb_player = 0;

    for (const auto &object : _loot) {
        if (object.name == "player" && object.position == 0)
            nb_player++;
    }
    if (_level == 1 && nb_player >= 1)
        return true;
    if ((_level == 2 || _level == 3) && nb_player >= 2)
        return true;
    if ((_level == 4 || _level == 5) && nb_player >= 4)
        return true;
    if ((_level == 6 || _level == 7) && nb_player >= 6)
        return true;
    return false;
}

bool Player::notMyMessage()
{
    auto pos = msg.find(' ');
    auto text = msg.substr(pos + 1);

    pos = text.find('\n');
    text.erase(pos, 1);

    if (text != _name)
        return true;
    return false;
}