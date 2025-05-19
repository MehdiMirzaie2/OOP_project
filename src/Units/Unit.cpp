#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"

#include <chrono>
#include <thread>

#define SOUL_SPEED 2

Unit::Unit() : Entity() {};

Unit::Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, std::string textureName) : Entity(dmg, loc_x, loc_y, spd, radius_atk, cst), HP(hp), isPicked(false)
{ // Sync sprite & user pos
    if (!texture.loadFromFile("src/Textures/" + std::string(textureName)))
    {
        std::cout << "Unable to load texture!\n";
    }
    attacks.resize(5);
    for (int i = 0; i < 5; i++){
        attacks[i] = Attack(this);
    }
    if (!deadTexture.loadFromFile("src/Textures/death.png")){
        std:: cout << "Couldnt load death soul\n";
    }
    skin.setTexture(texture);
    skin.setScale(UNITSIZE); 
    updateSpriteLoc();
    isAttacking = false;
    attackCooldown = sf::seconds(1);
    isDead = false;
};

std::vector<Attack*> Unit::active_attacks = {};

void Unit::useAttack()
{ // Use all attack sprites
    
    isAttacking = true;
}

float Unit::getHP()
{
    return HP;
};

void Unit::setHP(float newHP)
{
    HP = newHP;
}

void Unit::updateSpriteLoc()
{
    skin.setPosition(sf::Vector2f(this->getLocation().x, this->getLocation().y));
}

bool Unit::getisDead()
{
    return isDead;
}

void Unit::draw(sf::RenderWindow *window)
{
    updateSpriteLoc();
    window->draw(skin);

    if (isAttacking){
       attemptShooting();
    }
    for (int i = 0; i < 5; i++)
    {
        if (attacks[i].getisActive())
        {
            attacks[i].move();
            attacks[i].draw(window);
        }
    }
}

std::vector<Attack> Unit::getAttacks(){
    return attacks;
}

sf::Sprite Unit::getSkin(){return skin;}

void Unit::attemptShooting()
{   
     if (attackClock.getElapsedTime() >= attackCooldown){
         for (int i = 0; i < 5; i++)
        {
            if (!attacks[i].getisActive())
            {
                attackClock.restart();
                attacks[i].shoot(this->getFloatLoc());
                active_attacks.push_back(&attacks[i]);
                std:: cout << "Attack added: " << active_attacks[active_attacks.size() - 1]->describe() << std:: endl;
                break;
            }
        }
     }
}

void Unit::dead(){
    
    skin.setTexture(deadTexture);
    isDead = true;
}

// take damage from attack

void Unit::dying_animation()
{
    // MAKES THE SOUL MOVE UP
    // if (isDead){
    //     skin.move(SOUL_SPEED);
        
    // }
}

void Unit::takeDamage(Attack attack)
{
    if (HP <= 0){
        dead();
        return;
    }
    std:: cout << "Original HP: " << HP << std:: endl;
    this->HP -= attack.getDamage();
    std:: cout << "Remaining HP: " << HP << std:: endl;

    
}