#include "../../include/Game.hpp"

Game::Game(){

}

void Game::runGame(){
    bool playing = true;
    while (playing){
        int choice = menuWindow.runWindow();
        
        if(choice == 1){
            int winner = battleWindow.runWindow();
            
        }
        else if(choice == 2){
            customizeWindow.runWindow();
        }
        else{
            std:: cout << "Playing is false!\n";
            playing = false;
            break;
        }
    }
}
