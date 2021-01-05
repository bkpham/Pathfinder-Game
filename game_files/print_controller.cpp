#include "print_controller.hpp"

#include <iostream>

PrintController::~PrintController()
{
}

Command PrintController::getInput()
{
   
    char c;
    std::cin >> c;
    if(c == 'w')
        return Command::Forward;
    else if(c=='a')
        return Command::Left;
    else if(c=='d')
        return Command::Right;
    else if(c=='q')
        return Command::Quit;
    else
        return Command::Invalid;
}
