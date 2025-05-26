#ifndef CUSTOMIZEWINDOW_HPP_
#define CUSTOMIZEWINDOW_HPP_

#include "Window.hpp"
#include "Director.hpp"

class CustomizeWindow : public Window
{
private:
    Director director; // for building the customizations

public:
    CustomizeWindow();
    int runWindow();
};
#endif // CUSTOMIZEWINDOW_HPP_