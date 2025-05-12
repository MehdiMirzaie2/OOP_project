#ifndef CUSTOMIZEWINDOW_HPP_
#define CUSTOMIZEWINDOW_HPP_

#include "Window.hpp"

class CustomizeWindow : public Window
{
    private:
        Director director;
        User player;
    
    public:
        int runWindow();
}
#endif // CUSTOMIZEWINDOW_HPP_