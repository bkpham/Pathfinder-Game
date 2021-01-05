#ifndef PRINT_VIEW_HPP
#define PRINT_VIEW_HPP

#include "view.hpp"

class PrintView : public View
{
public:  // public methods
    PrintView(int height, int width);
    virtual ~PrintView();
    PrintView(const PrintView&) = delete;
    PrintView& operator=(const PrintView&) = delete;
    virtual void draw(const std::vector<std::string>& lines) override;
};

#endif // PRINT_VIEW_HPP
