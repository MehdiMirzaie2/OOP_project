#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"

#include <chrono>
#include <thread>

// How quickly the souls vanish from the battlefield
#define SOUL_SPEED 10

Unit::Unit() : Entity() {};

Unit::Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp, std::string idleTextureName, std::string attackingTextureName, std::string projectileTextureName, int alliance) : Entity(dmg, location, spd, radius_atk, cst), HP(hp), isPicked(false)
{ // Sync sprite & user pos
    if (!unitTextureIdle.loadFromFile("src/Textures/" + std::string(idleTextureName)))
    {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!unitTextureAttacking.loadFromFile("src/Textures/" + std::string(attackingTextureName)))
    {
        std::cout << "Unable to load attacking texture!\n";
    }
    this->projectileTextureName = projectileTextureName;

    // for (int i = 0; i < 5; i++){
    //     attacks.push_back(new Attack(this, projectileTextureName));
    // }

    if (!deadTexture.loadFromFile("src/Textures/death.png"))
    {
        std::cout << "Couldnt load death soul\n";
    }
    skin.setOrigin(unitTextureIdle.getSize().x / 2.f, unitTextureIdle.getSize().y / 2.f);
    skin.setTexture(unitTextureIdle);
    //skin.setScale(0.06f, 0.06f);
    std::cout << "texture size = " << unitTextureIdle.getSize().x << " " << unitTextureIdle.getSize().y << "\n";
    skin.setScale(30.0f / unitTextureIdle.getSize().x, 30.0f / unitTextureIdle.getSize().y);
    isAttacking = false;
    attackCooldown = sf::seconds(1);
    isDead = false;
    current_target = nullptr;
    timeSinceDeath.restart();
    this->alliance = alliance;
};

std::vector<Attack *> Unit::active_attacks = {};

void Unit::useAttack(Unit *hunted_target)
{ // Use all attack sprites
    current_target = hunted_target;
    isAttacking = true;
    isMovingForward = false;
}

void Unit::startMovingForward()
{
    isMovingForward = true;
    isAttacking = false;
    current_target = nullptr;
    MoveClock.restart();
}

float Unit::getHP()
{
    return HP;
};

void Unit::setHP(float newHP)
{
    HP = newHP;
}

void Unit::updateLocation(sf::Vector2f location)
{
    skin.setPosition(location);
}

void Unit::setDeckPosition(sf::Vector2f location)
{
    m_deckPos = location;
}

sf::Vector2f Unit::getDeckPosition()
{
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
    if (!isActive)
        return;

    if (isDead)
    {
        dying_animation();
        return;
    }

    if (isAttacking) // Attacking textures/Animations
    {
        if (skin.getTexture() != &unitTextureAttacking)
        {
            skin.setTexture(unitTextureAttacking);
        }
        if (!current_target->getisDead())
        {
            attemptShooting(); // Handles cooldown and firing
        }
        else
        {
            startMovingForward(); // Handles disabling of attacks and starts movement
        }
    }
    else
    {
        if (skin.getTexture() != &unitTextureIdle)
        {
            skin.setTexture(unitTextureIdle);
        }
    }

    // Movement Logic
    if (isMovingForward)
    {
        std::cout << "Unit is moving with alliance : " << alliance << std::endl;
        if (alliance == 0)
        { // 0 means move right
            skin.move(speed, 0);
        }
        else
        { // else move left
            skin.move(-speed, 0);
        }
    }
}

void Unit::update(Map &map) // Handles Unit Animations
{
    //std::cout << "hello world hello world\n";
    //(void)miap;
    if (!isActive)
        return;

    if (isDead)
    {
        dying_animation();
        return;
    }

    if (isAttacking) // Attacking textures/Animations
    {
        if (skin.getTexture() != &unitTextureAttacking)
        {
            skin.setTexture(unitTextureAttacking);
        }
        if (!current_target->getisDead())
        {
            attemptShooting(); // Handles cooldown and firing
        }
        else
        {
            int col = (skin.getPosition().x - 100) / 30, row = skin.getPosition().y / 30;
            setPath(map.aStarSearch(std::make_pair(row, col), getClosestTower()));
            startMovingForward(); // Handles disabling of attacks and starts movement
        }
    }
    else
    {
        if (skin.getTexture() != &unitTextureIdle)
        {
            skin.setTexture(unitTextureIdle);
        }
    }

    // Movement Logic
    if (isMovingForward && MoveClock.getElapsedTime() >= sf::seconds(speed))
    {
        if (!path.empty()) {
            Pair p = path.top();
	    path.pop();
            std::cout << p.first << " " << p.second << "\n";
            //skin.move((p.second * 30), (p.first + 30));
	    skin.setPosition((p.second * 30) + 100, p.first * 30);
        }
        else {
            std::cout << "path is empty\n";
        }
	MoveClock.restart();

        // int cols = (skin.getPosition().x - 100) / 30, rows = skin.getPosition().y / 30;
        // std::cout << "rows : " << rows << std::endl;
        // (void)cols;
        // float deltaX = 0, deltay = 0;
        // int xdirection = alliance == 1 ? -1 : 1;

        // if ((rows >= 2 && rows <= 4) || (rows >= 14 and rows <= 16))
        // {
        //     deltaX = speed * xdirection;
        //     deltay = 0;
        //     // skin.move(speed * xdirection, 0);
        // }

        // else if (rows <= 9)
        // {
        //     deltaX = 0;
        //     deltay = speed * -1;
        // }
        // else
        // {
        //     deltaX = 0;
        //     deltay = speed;
        // }

        // skin.move(deltaX, deltay);
        // std::cout << deltaX << " " << deltay << std::endl;
    }
}

void Unit::draw(sf::RenderWindow *window)
{
    window->draw(skin);

    if (isAttacking)
    {
        attemptShooting();
    }
}

Unit *Unit::getTarget()
{
    return current_target;
}

sf::Sprite Unit::getSkin() { return skin; }

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
    if (attackClock.getElapsedTime() >= attackCooldown)
    { // if the cooldown has passed

        Attack *projectile = new Attack(this, projectileTextureName, current_target);
        projectile->shoot(this->getLocation());
        active_attacks.push_back(projectile);
        attackClock.restart();
    }
}

void Unit::dead()
{

    skin.setOrigin(deadTexture.getSize().x / 2.f, deadTexture.getSize().y / 2.f);
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
        if (skin.getTexture() != &deadTexture)
        {
            skin.setTexture(deadTexture);
        }
        sf::Color current_color = skin.getColor();
        // std:: cout << "time passed since death: " << timeSinceDeath.getElapsedTime().asSeconds() << std:: endl;
        sf::Color newColor(current_color.r, current_color.g, current_color.b, 255 / (timeSinceDeath.getElapsedTime().asSeconds() * SOUL_SPEED));
        skin.setColor(newColor); // Based on the amount of time since death, change opacity
        if (skin.getColor().a <= 0.01)
        {
            std::cout << "Enough time has passed...\n";
            isActive = false;
        }
    }
}

void Unit::takeDamage(Attack attack)
{

    if (HP <= 0 && !isDead)
    {
        dead();
        return;
    }

    if (isDead)
    {
        return;
    }
    std::cout << "Original HP: " << HP << std::endl;
    this->HP -= attack.getDamage();
    std::cout << "Remaining HP: " << HP << std::endl;
}

sf::Sprite Unit::getSprite()
{
    return skin;
}

void Unit::moveIfPicked(sf::Vector2i mouse_pos)
{
    if (isPicked)
    {
        sf::Vector2f location(
            mouse_pos.x - dydx.x,
            mouse_pos.y - dydx.y);
        setLocation(location);
    }
}

void Unit::setIsPicked(bool status)
{
    isPicked = status;
}

bool Unit::getIsPicked()
{
    return isPicked;
}

void Unit::setDydx(sf::Vector2i _dydx)
{
    dydx = _dydx;
}

Pair Unit::getClosestTower()
{
	std::cout << "alience == " << alliance << "\n";
    int col = skin.getPosition().x / 30, row = skin.getPosition().y / 30;
    std::vector<Pair> targets =
        (alliance == 1) ? std::vector<Pair>{std::make_pair(3, 7), std::make_pair(8, 4), std::make_pair(9, 4), std::make_pair(14, 7)}
                        : std::vector<Pair>{std::make_pair(3, 24), std::make_pair(8, 27), std::make_pair(9, 27),std::make_pair(14, 24)};

    float min = __FLT_MAX__;
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        double distance = ((row - targets[i].first) * (row - targets[i].first)) + ((col - targets[i].second) * (col - targets[i].second));
	distance *= distance;
        if (distance < min)
        {
            min = distance;
            index = i;
        }
    }
    std::cout << targets[index].first << " " << targets[index].second << "\n"; 
    return targets[index];
}

void Unit::setPath(std::stack<Pair> _path) {
    path = _path;
}
