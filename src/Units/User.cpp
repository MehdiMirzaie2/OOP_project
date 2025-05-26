#include "../../include/User.hpp"

User::User(){};

User::User(std:: string name){
    this->name = name;
    wins = 0;
    losses = 0;
    towers = {nullptr};
    unitDeck = std::make_unique<Deck>();
    king = std::unique_ptr<Unit> (unitDeck->generateKing(0));
    
    sf::Sprite king_sprite = king->getSkin();
    sf::Vector2f current_scale = king_sprite.getScale();
    std:: cout << "current scale: " << current_scale.x << std::endl;
    king_sprite.setScale(current_scale.x*5, current_scale.y*5);
    std:: cout << "current scale: " << king_sprite.getScale().x << std::endl;

    
    king->describe();
    m_elixir = std::make_unique<Elixir>();

}

User::User(std:: string name, int left_or_right){
    this->name = name;
    wins = 0;
    losses = 0;
    towers = {nullptr};
    unitDeck = std::make_unique<Deck>(left_or_right);
    
    king = std::shared_ptr<Unit> (unitDeck->generateKing(left_or_right));
    sf::Sprite king_sprite = king->getSkin();
    sf::Vector2f current_scale = king_sprite.getScale();
    int flip = left_or_right == 0 ? 1 : -1;

    std:: cout << "current scale: " << current_scale.x << std::endl;
    king_sprite.setScale(flip*current_scale.x*5.f, current_scale.y*5.f);
    std:: cout << "current scale: " << king_sprite.getScale().x << std::endl;
   
    king->setSkin(king_sprite);
    king->setisActive(true);
    king->setisTower(true);
    
    king->describe();

    for(int i = 0; i < 2; i++)
    {
        towers[i] = std::shared_ptr<Unit> (unitDeck->generateTowers(left_or_right));
        sf::Sprite skin = towers[i]->getSkin();
        sf::Vector2f current_scale = skin.getScale();
        skin.setScale(current_scale.x*3.f, current_scale.y*3.f);
        towers[i]->setSkin(skin);
        towers[i]->setisActive(true);
        towers[i]->setisTower(true);
    }
    float offset = 35;
    sf::Vector2f top_left(WINDOW_WIDTH/4.5 + offset, WINDOW_HEIGHT/6 + offset);
    sf::Vector2f top_right(WINDOW_WIDTH - WINDOW_WIDTH/4.5 - offset, WINDOW_HEIGHT/6 + offset);
    sf::Vector2f bottom_left(WINDOW_WIDTH/4.5 + offset, WINDOW_HEIGHT - WINDOW_HEIGHT/6 - offset);
    sf::Vector2f bottom_right(WINDOW_WIDTH - WINDOW_WIDTH/4.5 - offset, WINDOW_HEIGHT - WINDOW_HEIGHT/6 - offset);

    if (left_or_right == 0){
        towers[0]->setLocation(top_left);
        towers[1]->setLocation(bottom_left);
    }
    else{
        towers[0]->setLocation(top_right);
        towers[1]->setLocation(bottom_right);
    }
    
    Unit::active_units.push_back(towers[0]);
    Unit::active_units.push_back(towers[1]);
    Unit::active_units.push_back(king);
    m_elixir = std::make_unique<Elixir>();

}

Elixir* User::getElixir() {
	return m_elixir.get();
}

void User::update(sf::Vector2i mouse_pos) {
	m_elixir->update();

	for (const auto& unit: unitDeck->getUnits()) {
		unit->moveIfPicked(mouse_pos);
	}
}

void User::setLosses(int l){
    losses = l;
}

void User::setWins(int w){
    wins = w;
}

void User::setName(std::string new_name){
    name = new_name;
}
/*
void User::setElixir(int new_elixir){
    elixir = new_elixir;
}
*/
int User::getWins(){return wins;}
int User::getLosses(){return losses;}
std:: string User::getName(){return name;}

/*
int User::getElixir(){
    return elixir;
}
*/

// void User::fight_user(User other){
//     // to be done
// };


void User::draw(sf::RenderWindow* window){
    unitDeck->draw(window);
    king->draw(window);

    for(auto& tower : towers){
        tower->draw(window);
    }
}

Deck* User::getDeck(){
    return unitDeck.get();
}
/*
void User::deploy(int index, sf::Vector2f dep_loc)
{   
    int col = dep_loc.x / 30, row = dep_loc.y / 30;
    std::cout << row << " " << col << std::endl;
	Unit* unit = unitDeck->getUnits()[index].get();
    //sf::Vector2i screen_pos = sf::Vector2i(30 * dep_loc.x, 30 * dep_loc * 30);
    //dep_loc.x *= 30;
    //dep_loc.y *= 30;
	sf::Vector2f a = sf::Vector2f(col * 30, row * 30);
    unit->setLocation(a);
    std:: cout << "UNITS LOCATION: " << unit->getLocation().x << std::endl;
    unit->setisActive(true);
}

*/
