#include "print_view.hpp"

#include <iostream>

/**
 * The constructor and destructor shouldn't need anything added.
 */

PrintView::PrintView(int height, int width)
    : View(height, width)
{
}

PrintView::~PrintView()
{
}

void PrintView::draw(const std::vector<std::string>& lines)
{

    for(int i=0;i<mHeight+2;i++) {
        for (int j = 0; j < mWidth+2; j++)
            std::cout << lines[i][j];
        std::cout << std::endl;
    }

    // TODO: Implement.
}
