#include <SFML/Graphics.hpp>

// Constants (swapped for rotation) [for x, bigger is right, smaller is left] [for y, bigger is down, smaller is up]
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

const int TOWER_WIDTH = 90;
const int TOWER_HEIGHT = 60;


sf::RectangleShape createTower(float x, float y, sf::Color baseColor) {
    sf::RectangleShape tower(sf::Vector2f(TOWER_WIDTH, TOWER_HEIGHT)); 
    tower.setPosition(y, WINDOW_HEIGHT - x - TOWER_WIDTH); 
    tower.setFillColor(baseColor);
    tower.setOutlineThickness(2);
    tower.setOutlineColor(sf::Color::Black);
    return tower;
}
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "map4");

    // Background
    sf::RectangleShape grass(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    grass.setFillColor(sf::Color(100, 200, 100));

    sf::RectangleShape river(sf::Vector2f(120, WINDOW_WIDTH)); // width of the river
    river.setPosition(WINDOW_HEIGHT / 2 + 140, 0); // dome
    river.setFillColor(sf::Color(0, 150, 255));

    sf::RectangleShape laneLeft(sf::Vector2f(20, WINDOW_WIDTH));
    laneLeft.setPosition(WINDOW_HEIGHT / 2 + 120, 0);
    laneLeft.setFillColor(sf::Color(160, 140, 110));

    sf::RectangleShape laneRight(sf::Vector2f(20, WINDOW_WIDTH));
    laneRight.setPosition(WINDOW_HEIGHT / 2 + 260, 0); // pls dont touch......
    laneRight.setFillColor(sf::Color(160, 140, 110));

    // Towers (up to down, in order)
    sf::RectangleShape enemyKing = createTower(WINDOW_WIDTH / 2.9 - TOWER_WIDTH / 1, WINDOW_HEIGHT / 15, sf::Color::Red); //2 
    sf::RectangleShape enemyLeftPrincess = createTower(WINDOW_WIDTH / 3 - 300, 260, sf::Color::Red); // 3
    sf::RectangleShape enemyRightPrincess = createTower(WINDOW_WIDTH / 3 + 149, 260, sf::Color::Red); // 1

    // FIX........
    sf::RectangleShape playerKing = createTower(WINDOW_WIDTH / 2.9 - TOWER_WIDTH / 1, WINDOW_HEIGHT + 258, sf::Color::Blue); //2
    sf::RectangleShape playerLeftPrincess = createTower(WINDOW_WIDTH / 3 - 300, WINDOW_HEIGHT + 50, sf::Color::Blue); //3
    sf::RectangleShape playerRightPrincess = createTower(WINDOW_WIDTH / 3 + 149, WINDOW_HEIGHT + 50, sf::Color::Blue); //1

    // bridg/lane
    sf::RectangleShape enemyLane(sf::Vector2f(540, 50));
    enemyLane.setPosition(328, 166); 
    enemyLane.setFillColor(sf::Color(160, 140, 110));

    sf::RectangleShape playerLane(sf::Vector2f(540, 50));
    playerLane.setPosition(328, 616); 
    playerLane.setFillColor(sf::Color(160, 140, 110));
   
   
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(grass);
        window.draw(river);
        window.draw(laneLeft);
        window.draw(laneRight);
        window.draw(enemyLane);
        window.draw(playerLane);
    

        window.draw(enemyKing);
        window.draw(enemyLeftPrincess);
        window.draw(enemyRightPrincess);
        window.draw(playerKing);
        window.draw(playerLeftPrincess);
        window.draw(playerRightPrincess);
        

        window.display();

    }

    return 0;
}
