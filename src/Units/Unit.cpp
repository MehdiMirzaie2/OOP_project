#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"

#include <chrono>
#include <thread>

// How quickly the souls vanish from the battlefield
#define SOUL_SPEED 10

Unit::Unit() : Entity() {};

Unit::Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp, std::string idleTextureName, std:: string attackingTextureName, std:: string projectileTextureName, int alliance) : Entity(dmg, location, spd, radius_atk, cst), HP(hp), isPicked(false)
{ // Sync sprite & user pos
    if (!unitTextureIdle.loadFromFile("src/Textures/" + std::string(idleTextureName)))
    {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!unitTextureAttacking.loadFromFile("src/Textures/" + std::string(attackingTextureName))){
        std::cout << "Unable to load attacking texture!\n";
    }
    this->projectileTextureName = projectileTextureName;

    // for (int i = 0; i < 5; i++){
    //     attacks.push_back(new Attack(this, projectileTextureName));
    // }
    
    if (!deadTexture.loadFromFile("src/Textures/death.png")){
        std:: cout << "Couldnt load death soul\n";
    }
    skin.setOrigin(unitTextureIdle.getSize().x/2.f, unitTextureIdle.getSize().y/2.f);
    skin.setTexture(unitTextureIdle);
    
    if (alliance == 1){ // Mirror the sprite if its in the right deck
        skin.setScale(-0.06f, 0.06f);
    }
    else{
        skin.setScale(0.06f, 0.06f); 
    }
    isAttacking = false;
    attackCooldown = sf::seconds(2);
    isDead = false;
    current_target = nullptr;
    timeSinceDeath.restart();
    this->alliance = alliance;

    
};

std::vector<Attack*> Unit::active_attacks = {};

void Unit::useAttack(Unit* hunted_target)
{ // Use all attack sprites
    current_target = hunted_target;
    isAttacking = true;
    isMovingForward = false;
}

void Unit::startMovingForward(){ isMovingForward = true; isAttacking = false; current_target = nullptr;}

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

void Unit::setDeckPosition(sf::Vector2f location) {
	m_deckPos = location;
}

sf::Vector2f Unit::getDeckPosition() {
	return m_deckPos;
}

void Unit::updateSpriteLoc()
{
    skin.setPosition(sf::Vector2f(this->getLocation().x, this->getLocation().y));
}

bool Unit::getisDead()
{
    return isDead;
}

void Unit::update() // Handles Unit Animations
{
    if (!isActive) return;

    if (isDead)
    {
        dying_animation();
        return;
    }

    if (isAttacking) // Attacking textures/Animations
    {
        // if (skin.getTexture() != &unitTextureAttacking){
        //     skin.setTexture(unitTextureAttacking);
        // }
        
        if (!current_target->getisDead()){
       
            updateAttackAnimation();
            attemptShooting(); // Handles cooldown and firing
        }
        else{
            startMovingForward(); // Handles disabling of attacks and starts movement
        }
        
    }
    else{
        if (skin.getTexture() != &unitTextureIdle) {
            skin.setTexture(unitTextureIdle);
        }
    }

    // Movement Logic
    if (isMovingForward)
    {
        if (alliance == 0){ // 0 means move right
            skin.move(speed, 0);
        }
        else{ // else move left
            skin.move(-speed, 0);
        }
        
    }

}

void Unit::updateAttackAnimation()
{
    // In the first half of the cooldown, the state remains as attacking texture
    float first_half_after_attack = attackCooldown.asSeconds()/2;
    float elapsed_seconds = attackClock.getElapsedTime().asSeconds();
    float early_factor = 0.6; // Shorten the duration for attacking texture after using attack
    first_half_after_attack = first_half_after_attack*early_factor;
    if (elapsed_seconds <= first_half_after_attack && skin.getTexture() != &unitTextureAttacking){
        std::cout << "First half!!\n";
        std::cout << attackClock.getElapsedTime().asSeconds() << std:: endl;
        skin.setTexture(unitTextureAttacking);
    }
    // for the second half, IdleTexture, which changes just when it becomes attack time
    else if (elapsed_seconds > first_half_after_attack && elapsed_seconds < first_half_after_attack*2 && skin.getTexture() != &unitTextureIdle){
        std::cout << "Second half\n";
        skin.setTexture(unitTextureIdle);
    }

}

void Unit::draw(sf::RenderWindow *window)
{
    window->draw(skin);

    if (isAttacking){
       attemptShooting();
    }
}

Unit* Unit::getTarget(){
    return current_target;
}

sf::Sprite Unit::getSkin(){return skin;}

void Unit::attemptShooting()
{   
    //  if (attackClock.getElapsedTime() >= attackCooldown){
    //      for (int i = 0; i < 5; i++)
    //     {
    //         if (!attacks[i]->getisActive())
    //         {
    //             attackClock.restart();
    //             attacks[i]->shoot(this->getFloatLoc());
    //             active_attacks.push_back(attacks[i]);
    //             break;
    //         }
    //     }
    //  }
    if (attackClock.getElapsedTime() >= attackCooldown){ // if the cooldown has passed                                                          
                                                                       
        Attack* projectile = new Attack(this, projectileTextureName, current_target);
        projectile->shoot(this->getLocation());
        active_attacks.push_back(projectile);
        attackClock.restart();
    }
    
}

void Unit::dead(){
    
    skin.setOrigin(deadTexture.getSize().x/2.f, deadTexture.getSize().y/2.f);
    skin.setTextureRect(sf::IntRect(0, 0, deadTexture.getSize().x, deadTexture.getSize().y));
    skin.setTexture(deadTexture);
    
    isDead = true;
    isAttacking = false;
    isMovingForward = false;
    timeSinceDeath.restart();
}

// take damage from attack

void Unit::dying_animation()
{

    if (isDead)
    {
        if (skin.getTexture() != &deadTexture){
            skin.setTexture(deadTexture);
        }
        sf::Color current_color = skin.getColor();
        //std:: cout << "time passed since death: " << timeSinceDeath.getElapsedTime().asSeconds() << std:: endl;
        sf::Color newColor(current_color.r, current_color.g, current_color.b, 255/(timeSinceDeath.getElapsedTime().asSeconds()*SOUL_SPEED));
        skin.setColor(newColor); // Based on the amount of time since death, change opacity
        if (skin.getColor().a <= 0.01){
            
            isActive = false;
        }
    }


}

void Unit::takeDamage(Attack attack)
{

    if (HP <= 0 && !isDead){
        dead();
        return;
    }

    if (isDead){
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
		sf::Vector2f location(
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
