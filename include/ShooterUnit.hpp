#include "Unit.hpp"
#include <vector>

class ShooterUnit : public sf::Sprite {
public:
    ShooterUnit();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setCustomization(const std::string& customization);

    int HP;
    int damage;
    int speed;
    int radius_of_attack;
    int cost;

private:
    float fireInterval;
    sf::Clock fireClock;
    std::vector<sf::CircleShape> bullets;
    sf::Texture idleTexture;
    sf::Texture moveTexture;
};