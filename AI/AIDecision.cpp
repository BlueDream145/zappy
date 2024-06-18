/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** AI
*/

#include "AI.hpp"

/**
 * @brief This function uses the current Player state to take the best decision possible,
 * storing it in '_decision
 */
void AI::takeDecision(void)
{
    static int check = 0;

    if (_player.gotNewMsg() && _player.getLevel() > 1 && _player.hasItemToElevate() && _player.notMyMessage()) {
        if (_player.hasEnoughPlayerToElevate()) {
            _decision.action = Incantation;
            _player.setMessage("");
            return;
        }
        lookForPlayer();
        return;
    }
    if (_player.hasItemToElevate()) {
        if (_player.hasEnoughPlayerToElevate()) {
            _decision.action = Incantation;
            return;
        }
        _decision.action = Broadcast;
        _decision.parameters = _player.getName();
        return;
    }
    if (!_player.hasVision()) { // If player has no valid vision, query it
        _decision.action = Look;
        _player.setPosition(0);
        _player.setDirection(AHEAD);
        return;
    }
    if (check % 5 == 0) {
        _decision.action = Inventory;
        return;
    }
    check++;
    checkLoot();
}

/**
 * @brief Will check player loot to see what to do
 */
void AI::checkLoot(void)
{
    auto &loot = _player.getLoot();

    if (_player.getPosition() == loot.front().position) {
        _decision.action = Take;
        _decision.parameters = loot.front().name;
        _player.eraseFirstLoot();
        return;
    }
    if (_player.hasToGoUp(loot.front().position)) {
        makePlayerGoUp();
        return;
    }
    if (_player.hasToGoRight(loot.front().position)) {
        makePlayerGoRight();
        return;
    }
    if (_player.hasToGoLeft(loot.front().position)) {
        makePlayerGoLeft();
        return;
    }
}

void AI::makePlayerGoUp(void)
{
    if (_player.getDirection() == RIGHT) {
            _player.setDirection(AHEAD);
            _decision.action = Left;
            return;
    }
    if (_player.getDirection() == LEFT) {
            _player.setDirection(AHEAD);
            _decision.action = Right;
            return;
    }
    if (_player.getPosition() == 0) // Update player position
        _player.setPosition(2);
    else if (_player.getPosition() >= 1 && _player.getPosition() <= 3)
        _player.setPosition(_player.getPosition() + 4);
    else if (_player.getPosition() >= 4 && _player.getPosition() <= 8)
        _player.setPosition(_player.getPosition() + 6);
    _decision.action = Forward;
}

void AI::makePlayerGoRight(void)
{
    if (_player.getDirection() == AHEAD) {
        _player.setDirection(RIGHT);
        _decision.action = Right;
        return;
    }
    _player.setPosition(_player.getPosition() + 1);
    _decision.action = Forward;
}

void AI::makePlayerGoLeft(void)
{
    if (_player.getDirection() == AHEAD) {
        _player.setDirection(LEFT);
        _decision.action = Left;
        return;
    }
    _player.setPosition(_player.getPosition() - 1);
    _decision.action = Forward;
}

void AI::lookForPlayer(void)
{
    auto k = _player.getMessage().substr(0, 1);

    if (k == "0") {
        _decision.action = Inventory;
        return;
    } else if (k == "2" || k == "1" || k == "8") {
        _decision.action = Forward;
        return;
    } else if (k == "5" || k == "6" || k == "7") {
        _decision.action = Right;
        return;
    } else if (k == "3" || k == "4") {
        _decision.action = Left;
        return;
    }
}