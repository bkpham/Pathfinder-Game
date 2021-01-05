#include "building.hpp"

const int Building::width = 6;
const int Building::height = 4;

Building::Building(int y, int x)
    : mY(y), mX(x)
{
}
void Building::drawIn(std::vector<std::string> &board) const {
    for(int i =0; i<height; i++)
        for(int j = 0; j< width; j++) {
            board[mY + i][mX + j] = '.';
            if(i == 2 && (j ==2 || j==3))
                board[mY + i][mX + j] = '&';
            if(i == 3 && (j ==2 || j==3))
                board[mY + i][mX + j] = '&';
        }
}
