/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Player
*/

#pragma once

//std::vector
#include <vector>
// std::string
#include <string>
// std::unordered_map
#include <unordered_map>

enum Action {
    NoneAction = 0,
    Forward,
    Left,
    Right,
    Look,
    Inventory,
    Broadcast,
    ConnectCount,
    Fork,
    Eject,
    Take,
    Set,
    Incantation
};

struct V2i
{
    int x = 0, y = 0;
};

struct Object
{
    std::string name;
    unsigned int position = 0;
};

enum Direction
{
    LEFT = 0,
    AHEAD,
    RIGHT
};

class Player
{
public:
    const std::string &getName(void) const { return _name; }
    void setName(const std::string &name) { _name = name; }

    const std::string &getMessage(void) const { return msg; }
    void setMessage(const std::string &message) { msg = message; }

    const V2i &getWorldSize(void) const { return _worldSize; }
    void setWorldSize(const V2i &worldSize) { _worldSize = worldSize; }

    unsigned int getLevel(void) const { return _level; }
    void setLevel(unsigned int level) { _level = level; }

    unsigned int getPosition(void) const { return position; }
    void setPosition(unsigned int pos) { position = pos; }

    Direction getDirection(void) const { return direction; }
    void setDirection(Direction d) { direction = d; }

    void eraseFirstLoot(void) { _loot.erase(_loot.begin()); }
    const std::vector<Object> &getLoot(void) const {return _loot; }

    unsigned int getItemCount(const std::string &name);
    void setItemCount(const std::string &name, unsigned int count);
    void parseInventory(const std::string &inventory);
    void parseLookCommand(const std::string &look);
    void filterLoot(void);

    bool isAlive(void) const noexcept { return _alive; }
    void die(void) { _alive = false; }

    bool hasVision(void) const noexcept { return !_loot.empty(); }

    bool gotNewMsg(void) const noexcept { return !msg.empty(); }

    bool hasToGoUp(unsigned int pos) const;
    bool hasToGoRight(unsigned int pos) const;
    bool hasToGoLeft(unsigned int pos) const;

    bool hasItemToElevate(void);
    bool hasEnoughPlayerToElevate(void);

    bool notMyMessage(void);
private:
    std::unordered_map<std::string, unsigned int> _inventory;
    std::string _name;
    V2i _worldSize;
    unsigned int _level = 1;
    unsigned int position = 0;
    Direction direction = AHEAD;
    bool _alive = true;
    std::vector<Object> _loot;
    std::string msg;
};