#include "../../include/BattleWindow.hpp"

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


BattleWindow::BattleWindow(){
    user1 = User("Adi");
    user2 = User("Mehdi");
    window = nullptr;
    m_turn = 0;
    
}

void BattleWindow::loadDecks() {
	//int numb
	for (int i = 0; i < 2; i++) {
		Deck* unitDeck = (i == 0) ? user1.getDeck() : user2.getDeck();
		
		for(int i = 0; i < MAX_UNITS; i++) {
        		Unit* newUnit = director.buildRanger();
        		
			if (newUnit)
				unitDeck->addUnit(newUnit); // addUnit should handle current_no_units
        		else 
            			std::cerr << "Failed to build ranger for deck population." << std::endl;
    		}

	}
}


void BattleWindow::deploye(sf::Event event) {
	

	if (num_deployed[m_turn] < 5) {
		std::cout << "this is user " << m_turn << "\n";
		User *user = (m_turn == 0) ? &user1 : &user2;
		//std::cout << user << std::endl;
		Deck* unitDeck = user->getDeck();
		Unit* unitToDeploy = unitDeck->getUnits()[num_deployed[m_turn]];

       		if (unitToDeploy != nullptr && !unitToDeploy->getisActive()) {
          		sf::Vector2i deployPos(event.mouseButton.x, event.mouseButton.y);
          

          		user->deploy(num_deployed[m_turn], deployPos); // Pass index and position

			num_deployed[m_turn]++;
			m_turn = (m_turn == 0) ? 1 : 0;
       		}
	} else {
		std::cout << "player " << m_turn << " has deployed " << num_deployed[m_turn] << "\n";
	 }	
}

int BattleWindow:: runWindow() // Used prompt to do deployment (Not my part)
{

    std::cout << "Populating deck initially..." << std::endl;
	loadDecks();
    //Deck* unitDeck = user1.getDeck();
    



    this->window = new sf::RenderWindow(sf::VideoMode(910,560), "BattleWindow");
    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }

            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left){
			std::cout << "calling delpue\n";
			deploye(event);
						
            }
        }

        //window->clear(sf::Color::Black); // Clear with a distinct color for debugging
        draw_all(window);
        //window->display();
    }
    }
    return 0;
}

void BattleWindow::draw_all(sf::RenderWindow* window){
    window->clear();
	gameMap.draw(window);

    user2.draw(window);
	user1.draw(window);
window->display();
}

