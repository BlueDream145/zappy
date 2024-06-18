/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main
*/

#include "IrrlichtApp.hpp"
#include "App/AppFactory.hpp"
#include "GameScreen.hpp"

static void RegisterCustomTypes(void);

int main(void)
{
    try {
        oA::IrrlichtApp app(true);

        RegisterCustomTypes();
        app.parseFile("Graphical/Design/Main.oA");
        app.run();
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}

static void RegisterCustomTypes(void)
{
    oA::AppFactory::Register<GameScreen>();
}