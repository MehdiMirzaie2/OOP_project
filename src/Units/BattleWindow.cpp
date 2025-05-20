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

/*need to change the background png, made a mistake, some rows are narrower than others*/ 


BattleWindow::BattleWindow(){
    user1 = User("Adi", 0);
    user2 = User("Mehdi", 1);
    window = nullptr;
    m_turn = 0;
    
}


void BattleWindow::deploye(sf::Event event) {
	if (num_deployed[m_turn] < 5) {

		std::cout << "this is user " << m_turn << "\n";
		User *user = (m_turn == 0) ? &user1 : &user2;
		//std::cout << user << std::endl;
		Deck* unitDeck = user->getDeck();
		Unit* unitToDeploy = unitDeck->getUnits()[num_deployed[m_turn]];

       		if (unitToDeploy != nullptr && !unitToDeploy->getisActive()) {
   			int col = (event.mouseButton.x - 100) / 30, row = event.mouseButton.y / 30;
			
			if (board[row][col] == 0 && ((m_turn == 0 && col < 14) || (m_turn == 1 && col > 15)) && user->getElixir()->getElixir() > 2) {
				//Unit* unit = user->unitDeck()getUnits()[num_deployed[m_turn]];
				sf::Vector2i a = sf::Vector2i((col * 30) + 100, row * 30);
				unitToDeploy->setLocation(a);
				unitToDeploy->setisActive(true);
				m_turn = (m_turn == 0) ? 1 : 0;	
				num_deployed[m_turn]++;
				board[row][col] = 2; // should be enums 
				user->getElixir()->decreaseElixir(3);
			}

			
       		}
	} else {
		std::cout << "player " << m_turn << " has deployed " << num_deployed[m_turn] << "\n";
	 }	
}

void BattleWindow::selectUnit(sf::Event event) {
	//(void)event;
	User *user = (m_turn == 0) ? &user1 : &user2;
	Deck *deck = user->getDeck();

	//sf::Vector2i mouse_pos = sf::Mouse::getPosition(this->window);
	std::cout << "sellecting units\n";

	std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
	for (auto unit: deck->getUnits()) {
		std::cout << "checking if sprte was slected\n";
		sf::Sprite sprite = unit->getSprite();
		std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
		if (sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {			
			unit->setIsPicked(true);
			//int dx = event.mouseButton.x - sprite.getPosition().x;
			//int dy = event.mouseButton.y - sprite.getPosition().y;
			//sf::Vector2i location(event.mouseButton.x - dx, event.mouseButton.y - dy);
			//unit->setLocation(location);
			std::cout << "updated location for a unit\n";
			
			//unit.isPicked = true;

sf::Vector2i location(
					event.mouseButton.x - sprite.getPosition().x,
					event.mouseButton.y - sprite.getPosition().y
			);
			unit->setDydx(location);
		}

	}
	std::cout << "\n\n";
}

int BattleWindow:: runWindow() // Used prompt to do deployment (Not my part)
{

	std::cout << "Populating deck initially..." << std::endl;
	//loadDecks();

    
	//this->window = new sf::RenderWindow(sf::VideoMode(910,560), "BattleWindow");
	this->window = new sf::RenderWindow(sf::VideoMode(1110,560), "BattleWindow");
	while(window->isOpen()){
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*(this->window));
        	sf::Event event;

		while(window->pollEvent(event)){
            		if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseButtonReleased) {
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
		draw_all(window);
		user1.update(mouse_pos);
		user2.update(mouse_pos);
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

