#include "../../include/Game.hpp"
#include <fstream>
#include <sstream>

Game::Game(){
    statsFile = "stats.txt";
}

void Game::runGame(){
    bool playing = true;
    while (playing){
        
        int choice = m_menuWindow.runWindow();
        
        if(choice == 1){
            int winner = m_battleWindow.runWindow();
            registerWinner(winner);
        }
        else if(choice == 2){
            int back = m_statsWindow.runWindow(statsFile);
            std:: cout << "statwindow returned; " << back << std::endl;
        }
        else{
            std:: cout << "Playing is false!\n";
            playing = false;
            break;
        }
    }
}

void Game::registerWinner(int winner)
{
    // STATS FORMAT: 
    // Player 1 - wins/loss
    // Player 2 - wins/loss

    // Default stats
    int w1 = 0, l1 = 0, w2 = 0, l2 = 0;

    // Read stats
    std::ifstream in(statsFile);
    std::string line;

    if (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string temp;
        char slash;
        iss >> temp >> temp >> temp >> w1 >> slash >> l1;
    }

    if (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string temp;
        char slash;
        iss >> temp >> temp >> temp >> w2 >> slash >> l2;
    }
    in.close();

    // updating winners
    if (winner == 1) {
        w1++;
        l2++;
    } else {
        w2++;
        l1++;
    }

    // Overwrite data in file
    std::ofstream out(statsFile, std::ios::out | std::ios::trunc);
    out << "Player 1 - " << w1 << "/" << l1 << "\n";
    out << "Player 2 - " << w2 << "/" << l2 << "\n";
    out.close();

    std::cout << "Stats updated successfully\n";

}