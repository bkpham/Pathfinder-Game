#ifndef VIEW_HPP
#define VIEW_HPP

#include <string>
#include <vector>

class View
{
public:
    View(int height, int width);
    virtual ~View() = default;

    View(const View&) = delete;
    View& operator=(const View&) = delete;

    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }
    virtual void draw(const std::vector<std::string>& lines) = 0;

protected:
    int mHeight;
    int mWidth;
};

#endif // VIEW_HPP
