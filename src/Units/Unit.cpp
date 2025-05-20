#include "../../include/Unit.hpp"
#include "UnitBuilder.hpp"



Unit::Unit() : Entity() {};

Unit::Unit(float dmg, float loc_x, float loc_y, float spd, float radius_atk, int cst, int hp, std::string textureName) : Entity(dmg, loc_x, loc_y, spd, radius_atk, cst), HP(hp), isPicked(false)
{   // Sync sprite & user pos
    if (!texture.loadFromFile("src/Textures/" + std::string(textureName))){
        std::cout << "Unable to load texture!\n";
    }
    //std::cout << texture.size
    skin.setTexture(texture);
    //skin.setTextureRect(sf::IntRect(50, 20, 100, 100));
    skin.setScale(-1.f, 1.f);
    
    skin.setScale(UNITSIZE); //fefsf
	skin.setPosition(skin.getGlobalBounds().width, 0);
    updateSpriteLoc();
};


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

void Unit::draw(sf::RenderWindow* window){
    updateSpriteLoc();
    window->draw(skin);
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
