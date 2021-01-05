#include <iostream>
#include "curses_view.hpp"

/**
 * Side note: This class should probably be what is known as a singleton
 * class, i.e. a class that uses some setup (e.g. a static variable) to
 * prevent more than one instance of it from being created. I did not do this.
 */

CursesView::CursesView(int height, int width)
    : View(height, width)
{
    initscr();
    cbreak();
    noecho();

    // TODO: Implement. Set up curses.

}

CursesView::~CursesView()
{
    // TODO: Implement. Clean up curses.
    endwin();
}

void CursesView::draw(const std::vector<std::string>& lines)
{
    for(int i=0;i<mHeight+2;i++) {
        for (int j = 0; j < mWidth+2; j++) {
            move(i+3,j);
            addch(lines[i][j]);
        }
    }
    refresh();
    curs_set(0);
    refresh();


    // TODO: Implement.

}
