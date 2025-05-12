#ifndef GAMEDATAMANAGER_HPP_
#define GAMEDATAMANAGER_HPP_

#include "User.hpp"

class GameDataManager
// Handle all file input/output operations for saving and loading game state.
{
    private:
        User current_user_data;
    public:
        void saveData(const User& user, const std::string& filename);
        bool loadData(User& user, const std::string& filename);
}

#endif // GAMEDATAMANAGER_HPP_