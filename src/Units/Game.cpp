#include "../../include/Game.hpp"


Game::runGame(){
    
    int choice = MenuWindow->runWindow();
    if (choice == 0){
        BattleWindow->runWindow();
    }
    else if(choice == 1){
        CustomizeWindow->runWindow();
    }
    else if(choice == 2){
        return;
    }
    runGame();
}
