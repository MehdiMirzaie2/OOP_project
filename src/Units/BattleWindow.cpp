#include "../../include/BattleWindow.hpp"
#include <cmath>

int unitsDeployedCount = 0;

int board[18][30]  = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

/*need to change the background png, made a mistake, some rows are narrower than others*/ 


BattleWindow::BattleWindow(){
    user1 = User("Adi", 0);
    user2 = User("Mehdi", 1);
    window = nullptr;
    active_units = {};
    m_turn = 0;
}

void BattleWindow::deploye(sf::Event event) {
	std::cout << "this is user " << m_turn << "\n";
	
	User *user = (m_turn == 0) ? &user1 : &user2;
	Deck* unitDeck = user->getDeck();
	Unit* unitToDeploy = unitDeck->getPickedUnit();

	if (unitToDeploy == nullptr) {
		std::cout << "could not find picked\n";
	}

       	if (unitToDeploy != nullptr) {
		//std::cout << "got unit to deploy\n";
   		int col = (event.mouseButton.x - 100) / 30, row = event.mouseButton.y / 30;	

		unitToDeploy->setIsPicked(false);
		if (board[row][col] != 0 || user->getElixir()->getElixir() < 2) {
			std::cout << "did not deploy, because not enought\n";
			unitToDeploy->setLocation(unitToDeploy->getDeckPosition());
			return ;
		}

		if (board[row][col] == 0 && ((m_turn == 0 && col < 14) || (m_turn == 1 && col > 15)) && user->getElixir()->getElixir() > 2) {
				sf::Vector2f a = sf::Vector2f((col * 30) + 100, row * 30);
				unitToDeploy->setLocation(a);
				unitToDeploy->setisActive(true);
				m_turn = (m_turn == 0) ? 1 : 0;	
				num_deployed[m_turn]++;
				board[row][col] = 2; // should be enums 
				user->getElixir()->decreaseElixir(3);

		                active_units.push_back(unitToDeploy);
                		unitsDeployedCount++;
                		unitToDeploy->startMovingForward();
                // unitToDeploy->useAttack();

				std::cout << "\n\n\ndepoyed unit\n\n\n\n";
				
			}
			
			
       	}
		
		


}

void BattleWindow::selectUnit(sf::Event event) {
	//(void)event;
	User *user = (m_turn == 0) ? &user1 : &user2;
	Deck *deck = user->getDeck();

	//sf::Vector2i mouse_pos = sf::Mouse::getPosition(this-window);
	std::cout << "sellecting units\n";

	std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
	for (auto unit: deck->getUnits()) {
		//std::cout << "checking if sprte was slected\n";
		sf::Sprite sprite = unit->getSprite();
		std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
		if (sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {			
			unit->setIsPicked(true);
			std::cout << "updated location for a unit\n";
			

			sf::Vector2i dydx(
				event.mouseButton.x - sprite.getPosition().x,
				event.mouseButton.y - sprite.getPosition().y
			);
			unit->setDydx(dydx);
			break;
		}

	}
	std::cout << "\n\n";
}

int BattleWindow:: runWindow() 
{

	std::cout << "Populating deck initially..." << std::endl;
	//loadDecks();

    
	//this->window = new sf::RenderWindow(sf::VideoMode(910,560), "BattleWindow");
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BattleWindow");
	while(window->isOpen()){
        gameClock.restart();
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*(this->window));
        sf::Event event;

		while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					selectUnit(event);
				}
			}

            		if (event.type == sf::Event::MouseButtonReleased){
                		if (event.mouseButton.button == sf::Mouse::Left){
					deploye(event);
						
            			}
        		}
    		}

        // updateUnits(gameClock.getElapsedTime());
        updateUnits();
        updateAttacks();
        checkCollisions();

		draw_all(window);
		user1.update(mouse_pos);
		user2.update(mouse_pos);
    	}
    return 0;
}

void BattleWindow::updateUnits()
{
    for(long unsigned int i = 0; i < active_units.size(); i++){ // Updates all active units

        if (active_units[i]->getisActive()){
        
            startUnitAttack(active_units[i]);
            active_units[i]->update();
        }
        else
        {
            active_units.erase(active_units.begin() + i);
            i--;
        }
        
    }
}

void BattleWindow::startUnitAttack(Unit* attacker)
{
    for(Unit* unit : active_units)
    {
        if (unit == attacker || attacker->getisDead() || unit->getisDead() || attacker->getTarget() == unit){
																				// They are already fighting
            continue;
        }
        sf::Vector2f attacker_loc = attacker->getLocation();
        sf::Vector2f target_loc = unit->getLocation();
        float distance = std::sqrt((attacker_loc.x - target_loc.x)*(attacker_loc.x - target_loc.x) + (attacker_loc.y - target_loc.y)*(attacker_loc.y - target_loc.y));
        
        if (abs(distance) <= attacker->getRadius_of_attack()){
            attacker->useAttack(unit);
        }
    }
}

void BattleWindow::updateAttacks()
{
    for(Attack* attack : Unit::active_attacks){
        attack->update();
    }
}

void BattleWindow::draw_all(sf::RenderWindow* window){
    window->clear();    
    gameMap.draw(window);
    
    user1.draw(window);   
    user2.draw(window);
    for (Attack* attack_projectile : Unit::active_attacks) {
        
        if (attack_projectile != nullptr && attack_projectile->getisActive()) {
            attack_projectile->update();
            attack_projectile->draw(window);
        }
    }
    window->display();
}

void BattleWindow::checkCollisions()
{
    for(long unsigned int i = 0; i < Unit::active_attacks.size(); i++)
    {
        
        if (Unit::active_attacks[i]->isHit(active_units)){
            std:: cout << "Attack hit detected\n";
        };
    }
}

