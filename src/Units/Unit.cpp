#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"

#include <chrono>
#include <thread>

#define SOUL_SPEED 2

Unit::Unit() : Entity() {};

Unit::Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, std::string idleTextureName, std:: string attackingTextureName, std:: string projectileTextureName) : Entity(dmg, loc_x, loc_y, spd, radius_atk, cst), HP(hp), isPicked(false)
{ // Sync sprite & user pos
    if (!unitTextureIdle.loadFromFile("src/Textures/" + std::string(idleTextureName)))
    {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!unitTextureAttacking.loadFromFile("src/Textures/" + std::string(attackingTextureName))){
        std::cout << "Unable to load attacking texture!\n";
    }
    this->projectileTextureName = projectileTextureName;
    for (int i = 0; i < 5; i++){
        attacks.push_back(Attack(this, projectileTextureName));
    }
    if (!deadTexture.loadFromFile("src/Textures/death.png")){
        std:: cout << "Couldnt load death soul\n";
    }
    skin.setTexture(unitTextureIdle);
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

void Unit::startMovingForward(){ isMovingForward = true; }

float Unit::getHP()
{
    return HP;
};

void Unit::setHP(float newHP)
{
    HP = newHP;
}

void Unit::updateLocation(sf::Vector2f location) {
	skin.setPosition(location);
}


void Unit::updateSpriteLoc()
{
    skin.setPosition(sf::Vector2f(this->getLocation().x, this->getLocation().y));
}

bool Unit::getisDead()
{
    return isDead;
}

void Unit::update(sf::Time time_passed) // Handles Unit Animations
{
    if (!isActive || isDead) return;

    if (isAttacking) // Attacking textures/Animations
    {
        if (skin.getTexture() != &unitTextureAttacking){
            skin.setTexture(unitTextureAttacking);
        }
        attemptShooting(); // Handles cooldown and firing
    }
    else{
        if (skin.getTexture() != &unitTextureIdle) {
            skin.setTexture(unitTextureIdle);
        }
    }

    // Movement Logic
    if (isMovingForward)
    {
        sf::Vector2f current_pos = getFloatLoc();
        setLocation(sf::Vector2i(current_pos.x + speed*time_passed.asSeconds(), current_pos.y));
    }

    updateSpriteLoc();

}

void Unit::draw(sf::RenderWindow *window)
{
    updateSpriteLoc();
    window->draw(skin);

    if (isAttacking){
       attemptShooting();
    }
    // for (int i = 0; i < 5; i++)
    // {
    //     if (attacks[i].getisActive())
    //     {
    //         attacks[i].move();
    //         attacks[i].draw(window);
    //     }
    // }
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

sf::Sprite Unit::getSprite() {
	return skin;
}

void Unit::moveIfPicked(sf::Vector2i mouse_pos) {
	if (isPicked) {
		sf::Vector2i location(
			mouse_pos.x - dydx.x,					
			mouse_pos.y - dydx.y
		);
		setLocation(location);
	}
}

void Unit::setIsPicked(bool status) {
	isPicked = status;
}

bool Unit::getIsPicked() {
	return isPicked;
}

void Unit::setDydx(sf::Vector2i _dydx) {
	dydx = _dydx;
}
