#include "../../include/Game.hpp"
#include <fstream>
#include <sstream>

Game::Game(){
    m_battleWindow = BattleWindow(&m_user1, &m_user2);
}

void Game::runGame(){
    bool playing = true;
    while (playing){
        int choice = m_menuWindow.runWindow();
        
        if(choice == 1){
            int winner = m_battleWindow.runWindow();
            registerWinner(winner);
            playing = false;
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

void Game::registerWinner(int winner)
{
    std::ofstream stats(statsFile, std::ios::app);

    std::string buffer_string = "";
    bool found_winner = false;
    bool found_loser = false;

    while(stats.getline(buffer_string)){
        std::istringstream iss(buffer_string);
        std::vector<std::string> words;
        std::string word;

        while (iss >> word) {
            words.push_back(word);
        }
        if (words[0] == m_user1.getName()){
            if (winner == 1){
                found_winner = true;
                std:: cout << "Found winner already in stats\n";
                int wins = std::stoi(words[1]);
                wins++;
                words[1].swap(std::to_string(wins));
            }
            else{
                found_loser = true;
                std::cout << "Found loser already in stats\n";
                int losses = std::stoi(words[1]);
                losses++;
                words[1].swap(std::to_string(losses));
            }
        }
        if (words[0] == m_user2.getName()){
             if (winner == 1){
                found_winner = true;
                std:: cout << "Found winner already in stats\n";
                int wins = std::stoi(words[1]);
                wins++;
                words[1].swap(std::to_string(wins));
            }
            else{
                found_loser = true;
                std::cout << "Found loser already in stats\n";
                int losses = std::stoi(words[1]);
                losses++;
                words[1].swap(std::to_string(losses));
            }
        }
    }

    if (found_winner == 0){
        if (winner == 1){
            std::string win_msg = m_user1.getName() + std::to_string(m_user1.getWins()) + std::to_string(m_user1.getLosses());
            stats << win_msg;
        }
        else{
            std::string win_msg = m_user2.getName() + std::to_string(m_user2.getWins()) + std::to_string(m_user2.getLosses());
            stats << win_msg;
        }
    }
    else if(found_loser == 0){
        if (winner == 1){
            std::string loss_msg = m_user2.getName() + std::to_string(m_user1.getWins()) + std::to_string(m_user2.getLosses());
            stats << loss_msg;
        }
        else{
            std::string loss_msg = m_user1.getName() + std::to_string(m_user1.getWins()) + std::to_string(m_user1.getLosses());
            stats << loss_msg;
        }
    }
    
}