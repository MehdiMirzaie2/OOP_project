#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"

#include <chrono>
#include <thread>

// How quickly the souls vanish from the battlefield
#define SOUL_SPEED 10

Unit::Unit() : Entity() {};

Unit::Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp, std::string idleTextureName, std::string attackingTextureName, std::string projectileTextureName, int alliance)
    : Entity(dmg, location, spd, radius_atk, cst),
      HP(hp),
      projectileTextureName(projectileTextureName),
      unitTextureIdleName(idleTextureName),
      unitTextureAttackingName(attackingTextureName),
      isPicked(false),
	isAttacking(false)
{ // Sync sprite & user posi
    int flip = alliance == 0 ? 1 : -1;
    std::cout << idleTextureName << std::endl;
    if (!unitTextureIdle.loadFromFile("src/Textures/" + std::string(idleTextureName)))
    {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!unitTextureAttacking.loadFromFile("src/Textures/" + std::string(attackingTextureName)))
    {
        std::cout << "Unable to load attacking texture!\n";
    }
    this->projectileTextureName = projectileTextureName;

    if (!deadTexture.loadFromFile("src/Textures/death.png"))
    {
        std::cout << "Couldnt load death soul\n";
    }

    skin.setTexture(unitTextureIdle);
    std::cout << "texture size = " << unitTextureIdle.getSize().x << " " << unitTextureIdle.getSize().y << "\n";
    skin.setScale(flip * (30.0f / unitTextureIdle.getSize().x), 30.0f / unitTextureIdle.getSize().y);
    isAttacking = false;
    attackCooldown = sf::seconds(2);
    isDead = false;
    current_target = nullptr;
    timeSinceDeath.restart();
    this->alliance = alliance;
};
/*
Unit::Unit(const Unit &src)
    : Entity(src), // call the base class copy constructor
      HP(src.HP),
      attackCooldown(src.attackCooldown),
      projectileTextureName(src.projectileTextureName),
      unitTextureIdleName(src.unitTextureIdleName),
      unitTextureAttackingName(src.unitTextureAttackingName),
      alliance(src.alliance),
      isPicked(src.isPicked),
      current_target(nullptr), // You probably don't want to copy the pointer as-is
      isAttacking(false),
      isDead(src.isDead)
{
    int flip = alliance == 0 ? 1 : -1;

    if (!unitTextureIdle.loadFromFile("src/Textures/" + src.projectileTextureName))
    {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!unitTextureAttacking.loadFromFile("src/Textures/" + src.unitTextureAttackingName))
    {
        std::cout << "Unable to load attacking texture!\n";
    }

    if (!deadTexture.loadFromFile("src/Textures/death.png"))
    {
        std::cout << "Couldnt load death texture\n";
    }

    // Setup sprite
    skin.setTexture(unitTextureIdle);
    skin.setScale(flip * (30.0f / unitTextureIdle.getSize().x), 30.0f / unitTextureIdle.getSize().y);

    // Reset clock/timers
    timeSinceDeath.restart();
}
*/
std::vector<std::unique_ptr<Attack>> Unit::active_attacks = {};
std::vector<std::shared_ptr<Unit>> Unit::active_units = {};

void Unit::useAttack(Unit *hunted_target)
{ // Use all attack sprites
    current_target = (hunted_target);
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
        if (!current_target->getisDead())
        {

            updateAttackAnimation();
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
        if (!path.empty())
        {
            Pair p = path.top();
            path.pop();
            std::cout << p.first << " " << p.second << "\n";
            // skin.move((p.second * 30), (p.first + 30));
            skin.setPosition((p.second * 30) + 100, p.first * 30);
        }
        else
        {
            // need to update, when tower is destroyed move to next tower
            std::cout << "path is empty\n";
        }
        MoveClock.restart();
    }
}

void Unit::updateAttackAnimation()
{
    // In the first half of the cooldown, the state remains as attacking texture
    float first_half_after_attack = attackCooldown.asSeconds() / 2;
    float elapsed_seconds = attackClock.getElapsedTime().asSeconds();
    float early_factor = 0.6; // Shorten the duration for attacking texture after using attack
    first_half_after_attack = first_half_after_attack * early_factor;
    if (elapsed_seconds <= first_half_after_attack && skin.getTexture() != &unitTextureAttacking)
    {
        std::cout << "First half!!\n";
        std::cout << attackClock.getElapsedTime().asSeconds() << std::endl;
        skin.setTexture(unitTextureAttacking);
    }
    // for the second half, IdleTexture, which changes just when it becomes attack time
    else if (elapsed_seconds > first_half_after_attack && elapsed_seconds < first_half_after_attack * 2 && skin.getTexture() != &unitTextureIdle)
    {
        std::cout << "Second half\n";
        skin.setTexture(unitTextureIdle);
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
    if (attackClock.getElapsedTime() >= attackCooldown)
    { // if the cooldown has passed
        std::unique_ptr<Attack> projectile = std::make_unique<Attack>(this, projectileTextureName, current_target);
        projectile->shoot(this->getLocation());
        active_attacks.push_back(std::move(projectile)); // Move ownership to active attacks for the attack.
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
                        : std::vector<Pair>{std::make_pair(3, 24), std::make_pair(8, 27), std::make_pair(9, 27), std::make_pair(14, 24)};

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

void Unit::setPath(std::stack<Pair> _path)
{
    path = _path;
}

int Unit::getAlliance()
{
    return alliance;
}

void Unit::bringToLife(sf::Vector2f pos, Map &gameMap)
{
    setLocation(pos);

    Unit::active_units.push_back(std::shared_ptr<Unit>(this));
    startMovingForward();
    setPath(gameMap.aStarSearch(std::make_pair(int((pos.x - 100) / 30), int(pos.y / 30)), getClosestTower()));
    setisActive(true);
    startMovingForward();

    std::cout << "\n\n\ndepoyed unit\n\n\n\n";
}
