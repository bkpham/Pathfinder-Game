//
// Created by Brandon on 12/9/2020.
//
#include <iostream>
#include "game.hpp"
#include "interface_type.hpp"
int main(int argc, char *argv[]) {
    InterfaceType it = InterfaceType::Print;
    if (argc >= 2) it = InterfaceType::Curses;
    Game g{"demo_game1.txt", InterfaceType::Print};
    g.run();
}