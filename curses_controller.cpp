#include "curses_controller.hpp"

#include <curses.h>

CursesController::~CursesController()
{
}

Command CursesController::getInput()
{
    char c;
    c = getch();

    if(c == 'w')
        return Command::Forward;
    else if(c=='a')
        return Command::Left;
    else if(c=='d')
        return Command::Right;
    else if(c=='q')
        return Command::Quit;
    else if(c == 27){
        c = getch();
        if(c==91){
            c = getch();
            if(c==65)
                return Command::Forward;
            else if(c == 67)
                return Command::Right;
            else if(c==68)
                return Command::Left;
            else
                return Command::Invalid;
        }
    }
    else
        return Command::Invalid;
    // TODO: Implement.
    // Don't forget about the arrow keys.

    // To prevent a compiler error in the starter files...
    return Command::Invalid;
}

