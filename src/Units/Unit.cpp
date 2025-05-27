#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"

#include <chrono>
#include <thread>

// How quickly the souls vanish from the battlefield
#define SOUL_SPEED 10

Unit::Unit() : Entity() {}

Unit::Unit(float dmg, float spd, sf::Vector2f location, float radius_atk, int cst, int hp, std::string idleTextureName, std::string attackingTextureName, std::string projectileTextureName, int alliance)
    : Entity(projectileTextureName, idleTextureName,attackingTextureName, dmg, location, spd, radius_atk, cst),
      m_HP(hp),
      m_isPicked(false),
      m_isAttacking(false)
{ // Sync sprite & user posi
    int flip = alliance == 0 ? 1 : -1;

    m_skin.setTexture(m_unitTextureIdle);
   if (m_unitTextureIdle.getSize().x > 0 && m_unitTextureIdle.getSize().y > 0)  
    {
        m_skin.setScale(flip * (30.0f / m_unitTextureIdle.getSize().x), 30.0f / m_unitTextureIdle.getSize().y);
    }
    else
    {
        std::cerr << "ERROR: Idle texture '" << idleTextureName << "' has zero dimensions. Setting default scale." << std::endl;
        m_skin.setScale(flip * 1.0f, 1.0f); 
    }
    m_isAttacking = false;
    m_attackCooldown = sf::seconds(2);
    m_isDead = false;
    m_current_target = nullptr;
    m_timeSinceDeath.restart();
    m_alliance = alliance;

    targets = (m_alliance == 1) ? std::vector<Pair>{std::make_pair(3, 6), std::make_pair(8, 3), std::make_pair(9, 3), std::make_pair(14, 6)}
                                : std::vector<Pair>{std::make_pair(3, 25), std::make_pair(8, 28), std::make_pair(9, 28), std::make_pair(14, 25)};
}

Unit::Unit(const std::shared_ptr<Unit> &src)
    : Entity(src->getProjectileTextureName(), src->getIdleTextureName(), src->getAttackingTextureName(), src->getDamage(), src->getLocation(), src->getSpeed(), src->getRadius_of_attack(), src->getCost()), // call the base class copy constructor
      m_HP(src->getHP()),
      m_isPicked(false),
      m_isAttacking(false)
{ // Sync sprite & user posi
  	std::cout << "\n\ncalling Unit copy constructor\n\n";
    int flip = src->getAlliance() == 0 ? 1 : -1;

    m_skin.setTexture(m_unitTextureIdle);
   if (m_unitTextureIdle.getSize().x > 0 && m_unitTextureIdle.getSize().y > 0)  
    {
        m_skin.setScale(flip * (30.0f / m_unitTextureIdle.getSize().x), 30.0f / m_unitTextureIdle.getSize().y);
    }
    else
    {
        std::cerr << "ERROR: Idle texture '" << m_unitTextureIdleName << "' has zero dimensions. Setting default scale." << std::endl;
        m_skin.setScale(flip * 1.0f, 1.0f); 
    }
    m_isAttacking = false;
    m_attackCooldown = sf::seconds(2);
    m_isDead = false;
    m_current_target = nullptr;
    m_timeSinceDeath.restart();
    m_alliance = src->getAlliance();

    targets = (m_alliance == 1) ? std::vector<Pair>{std::make_pair(3, 8), std::make_pair(8, 5), std::make_pair(9, 5), std::make_pair(14, 8)}
                                : std::vector<Pair>{std::make_pair(3, 23), std::make_pair(8, 26), std::make_pair(9, 26), std::make_pair(14, 23)};
}

std::vector<std::unique_ptr<Attack>> Unit::active_attacks = {};
std::vector<std::shared_ptr<Unit>> Unit::active_units = {};
std::unordered_set<Pair, pair_hash> Unit::dead_towers;

void Unit::useAttack(Unit *hunted_target)
{ // Use all attack sprites

    m_current_target = (hunted_target);
    m_isAttacking = true;
    m_isMovingForward = false;
}

void Unit::startMovingForward()
{
    if (m_isTower){
        m_isAttacking = false;
        m_current_target = nullptr;
        m_MoveClock.restart();
        return;
    }
    m_isMovingForward = true;
    m_isAttacking = false;
    m_current_target = nullptr;
    m_MoveClock.restart();
}

float Unit::getHP()
{
    return m_HP;
};

void Unit::setHP(float newHP)
{
    m_HP = newHP;
}

void Unit::updateLocation(sf::Vector2f location)
{
    m_skin.setPosition(location);
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
    m_skin.setPosition(sf::Vector2f(this->getLocation().x, this->getLocation().y));
}

bool Unit::getisDead()
{
    return m_isDead;
}

void Unit::update() // Handles Unit Animations
{
    if (!m_isActive)
        return;

    if (m_isDead)
    {
        dying_animation();
        return;
    }

    if (m_isAttacking) // Attacking textures/Animations
    {
        if (!m_current_target->getisDead())
        {

            updateAttackAnimation();
            attemptShooting(); // Handles cooldown and firing
        }
        else
        {
            if (!m_isTower)
            {
                startMovingForward(); // Handles disabling of attacks and starts movement
            }
        }
    }
    else
    {
        if (m_skin.getTexture() != &m_unitTextureIdle)
        {
            m_skin.setTexture(m_unitTextureIdle);
        }
    }

    // Movement Logic
    if (m_isMovingForward)
    {
        if (m_alliance == 0)
        { // 0 means move right
            m_skin.move(m_speed, 0);
        }
        else
        { // else move left
            m_skin.move(-m_speed, 0);
        }
    }
}

void Unit::update(Map &map) // Handles Unit Animations
{
    if (!m_isActive)
        return;

    if (m_isDead)
    {
        dying_animation();
        return;
    }

    if (m_isAttacking) // Attacking textures/Animations
    {
        if (m_skin.getTexture() != &m_unitTextureAttacking)
        {
            m_skin.setTexture(m_unitTextureAttacking);
        }
        if (!m_current_target->getisDead())
        {
            updateAttackAnimation();
            attemptShooting(); // Handles cooldown and firing
        }
        else
        {
            int col = (m_skin.getPosition().x - 100) / 30, row = m_skin.getPosition().y / 30;
            setPath(map.aStarSearch(std::make_pair(row, col), getClosestTower()));
            startMovingForward(); // Handles disabling of attacks and starts movement
        }
    }
    else
    {
        if (m_skin.getTexture() != &m_unitTextureIdle)
        {
            m_skin.setTexture(m_unitTextureIdle);
        }
    }

    // Movement Logic
    if (m_isMovingForward && m_MoveClock.getElapsedTime() >= sf::seconds(m_speed) && !m_isTower)
    {
        if (!m_path.empty())
        {
            Pair p = m_path.top();
            m_path.pop();
            m_skin.setPosition((p.second * 30) + 100, p.first * 30);
        }
        else
        {
            int col = (m_skin.getPosition().x - 100) / 30, row = m_skin.getPosition().y / 30;
            if (dead_towers.find(std::make_pair(row, col)) != dead_towers.end()) 
                setPath(map.aStarSearch(std::make_pair(row, col), getClosestTower()));
            // need to update, when tower is destroyed move to next tower
        }
        m_MoveClock.restart();
    }
}

void Unit::updateAttackAnimation()
{
    // In the first half of the cooldown, the state remains as attacking texture
    float first_half_after_attack = m_attackCooldown.asSeconds() / 2;
    float elapsed_seconds = m_attackClock.getElapsedTime().asSeconds();
    float early_factor = 0.6; // Shorten the duration for attacking texture after using attack
    first_half_after_attack = first_half_after_attack * early_factor;
    if (elapsed_seconds <= first_half_after_attack && m_skin.getTexture() != &m_unitTextureAttacking)
    {
        std::cout << m_attackClock.getElapsedTime().asSeconds() << std::endl;
        m_skin.setTexture(m_unitTextureAttacking);
    }
    // for the second half, IdleTexture, which changes just when it becomes attack time
    else if (elapsed_seconds > first_half_after_attack && elapsed_seconds < first_half_after_attack * 2 && m_skin.getTexture() != &m_unitTextureIdle)
    {
        m_skin.setTexture(m_unitTextureIdle);
    }
}

void Unit::draw(sf::RenderWindow *window)
{
    window->draw(m_skin);

    if (m_isAttacking)
    {
        attemptShooting();
    }
}

Unit *Unit::getTarget()
{
    return m_current_target;
}

sf::Sprite &Unit::getSkin() { return m_skin; }

void Unit::attemptShooting()
{
    if (m_attackClock.getElapsedTime() >= m_attackCooldown)
    { // if the cooldown has passed
        std::unique_ptr<Attack> projectile = std::make_unique<Attack>(this, m_projectileTextureName, m_current_target);
        projectile->shoot(this->getLocation());
        active_attacks.push_back(std::move(projectile)); // Move ownership to active attacks for the attack.
        m_attackClock.restart();
    }
}

void Unit::dead()
{
    if (m_isTower) {
	    
        dead_towers.insert(getClosestTower());
    }
    m_skin.setOrigin(m_deadTexture.getSize().x / 2.f, m_deadTexture.getSize().y / 2.f);
    m_skin.setTextureRect(sf::IntRect(0, 0, m_deadTexture.getSize().x, m_deadTexture.getSize().y));
    m_skin.setTexture(m_deadTexture);

    m_isDead = true;
    m_isAttacking = false;
    m_isMovingForward = false;
    m_timeSinceDeath.restart();
}

// take damage from attack

void Unit::dying_animation()
{

    if (m_isDead)
    {
        if (m_skin.getTexture() != &m_deadTexture)
        {
            m_skin.setTexture(m_deadTexture);
        }
        sf::Color current_color = m_skin.getColor();
        // std:: cout << "time passed since death: " << timeSinceDeath.getElapsedTime().asSeconds() << std:: endl;
        sf::Color newColor(current_color.r, current_color.g, current_color.b, 255 / (m_timeSinceDeath.getElapsedTime().asSeconds() * SOUL_SPEED));
        m_skin.setColor(newColor); // Based on the amount of time since death, change opacity
        if (m_skin.getColor().a <= 0.01)
        {
            m_isActive = false;
        }
    }
}

void Unit::setSkin(sf::Sprite _skin)
{
    m_skin = _skin;
}

bool Unit::getisTower()
{
    return m_isTower;
}

void Unit::setisTower(bool istower)
{
    m_isTower = istower;
}
void Unit::takeDamage(Attack attack)
{

    if (m_HP <= 0 && !m_isDead)
    {
        dead();
        return;
    }

    if (m_isDead)
    {
        return;
    }
    
    this->m_HP -= attack.getDamage();
    std::cout << "Remaining HP: " << m_HP << std::endl;
    if (m_HP <= 0){
        dead();
        return;
    }
}

sf::Sprite Unit::getSprite()
{
    return m_skin;
}


void Unit::moveIfPicked(sf::Vector2i mouse_pos)
{
    if (m_isPicked)
    {
        sf::Vector2f location(
            mouse_pos.x - m_dydx.x,
            mouse_pos.y - m_dydx.y);
        setLocation(location);
    }
}

void Unit::setIsPicked(bool status)
{
    m_isPicked = status;
}

bool Unit::getIsPicked()
{
    return m_isPicked;
}

void Unit::setDydx(sf::Vector2i _dydx)
{
    m_dydx = _dydx;
}

Pair Unit::getClosestTower()
{
    int col = m_skin.getPosition().x / 30, row = m_skin.getPosition().y / 30;
    float min = __FLT_MAX__;
    int index = 0;                                                                 

    for (int i = 0; i < 4; i++)
    {
	    

        if (dead_towers.find(targets[i]) == dead_towers.end())
        {
		
            double distance = ((row - targets[i].first) * (row - targets[i].first)) + ((col - targets[i].second) * (col - targets[i].second));
            distance *= distance;
            if (distance < min)
            {
                min = distance;
                index = i;
            }
        }
    }
    std::cout << targets[index].first << " " << targets[index].second << "\n";
    return targets[index];
}

void Unit::setPath(std::stack<Pair> _path)
{
    m_path = _path;
}

int Unit::getAlliance()
{
    return m_alliance;
}
