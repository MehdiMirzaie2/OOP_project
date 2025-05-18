#include "../../include/map.hpp"


Map::Map(){
   /* 
//    sf::RectangleShape grass(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
  //  grass.setFillColor(sf::Color(100, 200, 100));

    //sf::RectangleShape river(sf::Vector2f(120, WINDOW_WIDTH)); // width of the river
//    river.setPosition(WINDOW_HEIGHT / 2 + 140, 0); // move the river, dont touch pls pls!
 //   river.setFillColor(sf::Color(0, 150, 255));

    sf::RectangleShape laneLeft(sf::Vector2f(20, WINDOW_WIDTH));
    laneLeft.setPosition(WINDOW_HEIGHT / 2 + 120, 0);
    laneLeft.setFillColor(sf::Color(160, 140, 110));

    sf::RectangleShape laneRight(sf::Vector2f(20, WINDOW_WIDTH));
    laneRight.setPosition(WINDOW_HEIGHT / 2 + 260, 0); // pls dont touch......
    laneRight.setFillColor(sf::Color(160, 140, 110));
*/

	

	//sf::Texture map_texture;

	map_texture.loadFromFile("src/Units/b.png");
    std::cout << map_texture.getSize().x << " " << map_texture.getSize().y << " not map texture\n";
	map_sprite.setTexture(map_texture);
	if (map_sprite.getTexture() == NULL) 
		std::cout << map_sprite.getPosition().x << " this is the sprite\n";
	//map_sprite.setPosition(1, 1);
		
 // Towers (up to down, in order)
    auto enemyKing = createTower(WINDOW_WIDTH / 2.9 - TOWER_WIDTH / 1, WINDOW_HEIGHT / 3, sf::Color::Red); //2 
    auto enemyLeftPrincess = createTower(WINDOW_WIDTH / 3 - 300, 80, sf::Color::Red); // 3
    auto enemyRightPrincess = createTower(WINDOW_WIDTH / 3 + 149, 80, sf::Color::Red); // 1


    auto playerKing = createTower(WINDOW_WIDTH / 2.9 - TOWER_WIDTH / 1, WINDOW_HEIGHT + 45, sf::Color::Blue); //2
    auto playerLeftPrincess = createTower(WINDOW_WIDTH / 3 - 300, WINDOW_HEIGHT + 232, sf::Color::Blue); //3
    auto playerRightPrincess = createTower(WINDOW_WIDTH / 3 + 149, WINDOW_HEIGHT + 232, sf::Color::Blue); //1

     // bridg/lane
     /*
     sf::RectangleShape enemyLane(sf::Vector2f(540, 50));
     enemyLane.setPosition(328, 166); 
     enemyLane.setFillColor(sf::Color(160, 140, 110));
 
     sf::RectangleShape playerLane(sf::Vector2f(540, 50));
     playerLane.setPosition(328, 616); 
     playerLane.setFillColor(sf::Color(160, 140, 110));

    elements.insert(element("laneleft", laneLeft));
    elements.insert(element("laneright", laneRight));
    elements.insert(element("river", river));
    elements.insert(element("grass", grass));
    */
    elements.insert(element("playerKing", playerKing));
    elements.insert(element("playerLeftPrincess", playerLeftPrincess));
    elements.insert(element("playerRightPrincess", playerRightPrincess));
    elements.insert(element("enemyKing", enemyKing));
    elements.insert(element("enemyLeftPrincess", enemyLeftPrincess));
    elements.insert(element("enemyRightPrincess", enemyRightPrincess));
    //elements.insert(element("enemyLane", enemyLane));
    //elements.insert(element("playerLane", playerLane));
}


sf::RectangleShape Map::createTower(float x, float y, sf::Color baseColor) {
    sf::RectangleShape tower(sf::Vector2f(TOWER_WIDTH, TOWER_HEIGHT)); 
    tower.setPosition(y, WINDOW_HEIGHT - x - TOWER_WIDTH); 
    tower.setFillColor(baseColor);
    tower.setOutlineThickness(2);
    tower.setOutlineColor(sf::Color::Black);
    return tower;
}

void Map::draw(sf::RenderWindow* window){
	//std::cout << "hello world\n";
	if (map_sprite.getTexture() == NULL) 
		std::cout << "there is no texture " << map_sprite.getPosition().x << std::endl;
	window->draw(map_sprite);
    
	/*
    window->draw(elements["grass"]);
    window->draw(elements["river"]);
    window->draw(elements["laneLeft"]);
    window->draw(elements["laneRight"]);
    window->draw(elements["enemyKing"]);
    window->draw(elements["enemyLeftPrincess"]);
      
    window->draw(elements["enemyRightPrincess"]);
    window->draw(elements["playerKing"]);
    window->draw(elements["playerLeftPrincess"]);
    window->draw(elements["playerRightPrincess"]);

    window->draw(elements["playerLane"]);
    window->draw(elements["enemyLane"]);
*/
}


 // Background
 
