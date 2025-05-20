#ifndef UNITS_HEADER_MAP_HPP_
#define UNITS_HEADER_MAP_HPP_

// Constants (swapped for rotation)

const int TOWER_WIDTH = 90;
const int TOWER_HEIGHT = 60;

#include "Unit.hpp"
#include "Drawable.hpp"
#include <unordered_map>
#include <string>
#include <vector>

typedef std::pair<std::string, sf::RectangleShape> element;

class Map : public Drawable{
    private:
        int rows;
        int cols;
        std::unordered_map<std::string, sf::RectangleShape> elements;
	sf::Sprite map_sprite;
	sf::Texture map_texture;
	std::vector<std::vector<int>> map_grid;
       
    public:
        Map();
        void draw(sf::RenderWindow* window);
        sf::RectangleShape createTower(float x, float y, sf::Color baseColor);
        
};

#endif // UNITS_HEADER_MAP_HPP_
