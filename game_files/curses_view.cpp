#include <iostream>
#include "curses_view.hpp"


CursesView::CursesView(int height, int width)
    : View(height, width)
{
    initscr();
    cbreak();
    noecho();

}

CursesView::~CursesView()
{
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
}
