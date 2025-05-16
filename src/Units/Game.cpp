#include "../../include/Game.hpp"


Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "map4");
    user1 = User("myname");
}

void Game::draw_all(){
    gameMap.draw(window);
    user1.draw(window);
}

void Game:: runWindow()
{
    //Unit** user1_units = user1.getDeck().getUnits();
    
	sf::Texture t1;
	t1.loadFromFile("golum.png");

	sf::Sprite s(t1);
	bool isMove = false;
	float dx = 0, dy = 0;
    while(window->isOpen()){
        sf::Event event;
	sf::Vector2i pos = sf::Mouse::getPosition(*window);
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
            // unit spawn logic, keep disabled until completed by me.
	    //sf::Vector2i pos = sf::Mouse::getPosition(window); 
           if (event.type == sf::Event::MouseButtonPressed)
		if (event.key.code == sf::Mouse::Button::Left)
			if (s.getGlobalBounds().contains(pos.x, pos.y)) {
				isMove = true;
				dx = pos.x - s.getPosition().x;
				dy = pos.y - s.getPosition().y;
			}
	   if (event.type == sf::Event::MouseButtonReleased)
		   if (event.key.code == sf::Mouse::Button::Left)
			   isMove = false;
	}
	if (isMove) s.setPosition(pos.x - dx, pos.y - dx);
			//for (auto unit: user1.getDeck().getUnits()) {
			//	std::cout << 
                // bool* picks = user1.getDeck().getIsPicked();
                 //for(int i = 0; i < MAX_UNITS; i++){
                   //  if(picks[i]){
                         //deploy the unit at the desired location
                 //        user1.deploy(user1_units[i], sf::Mouse::getPosition(), window)
               //      }
             //    }
           //  }
            
        }
        
        window->clear();
        //draw_all();
	window->draw(s);
        window->display();
    }
