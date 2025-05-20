#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Drawable.hpp"

class Unit;


class Attack : public Drawable
// demo class for testing , might use for MVP
{
    private:
        sf::Texture attackTexture;
        sf::Sprite attackSprite;
        sf::Vector2f location;
        float speed;
        bool isActive;
        int damage;
        Unit* owner;
        Unit* target;

    public:
      
        Attack(Unit* owner, std::string attackTextureName, Unit* target);
        void move();
        bool getisActive();
        void draw(sf::RenderWindow* window);
        void updateLocation(sf::Vector2f new_loc);
        void shoot(sf::Vector2f shooting_location);
        void update();
        int getDamage();
        bool isHit(std::vector<Unit*> unitlist);
        std:: string describe();
};

#endif // ATTACK_HPP_