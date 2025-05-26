#include "../../include/Game.hpp"

Game::Game(){

}

void Game::runGame(){
    bool playing = true;
    while (playing){
        int choice = m_menuWindow.runWindow();
        
        if(choice == 1){
            m_battleWindow.runWindow();
        }
        else if(choice == 2){
            m_customizeWindow.runWindow();
        }
        else{
            std:: cout << "Playing is false!\n";
            playing = false;
            break;
        }
    }
}
