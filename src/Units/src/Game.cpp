#include "../header/Game.hpp"

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(200,200), "YES EYS");
}

void Game:: runGame()
{
    // Example: Create a circle shape to draw
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while(window->isOpen()){
        sf::Event event;
        while(window->pollEvent(event)){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                window->close();
            }
        }
        window->clear();

        // Draw the shape
        window->draw(shape);

        window->display();
    }
}