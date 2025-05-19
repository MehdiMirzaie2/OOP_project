#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Drawable.hpp"

class Attack : public Drawable
// demo class for testing , might use for MVP
{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        int speed;
        bool isActive;
    public:
        Attack();
        void move();
        bool getisActive();
        void draw(sf::RenderWindow* window);
        void updateLocation(sf::Vector2f new_loc);
        void shoot(sf::Vector2f shooting_location);
};

#endif // ATTACK_HPP_