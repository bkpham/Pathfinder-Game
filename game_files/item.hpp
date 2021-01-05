#ifndef ITEM_HPP
#define ITEM_HPP


class Item
{
public:
    Item(int y, int x);

    int getY() const { return mY; }
    int getX() const { return mX; }

    static char ICON;

private:
    int mY;
    int mX;
};

#endif // ITEM_HPP
