#ifndef UNITS_HEADER_MAP_HPP_
#define UNITS_HEADER_MAP_HPP_

// Constants (swapped for rotation)

const int TOWER_WIDTH = 90;
const int TOWER_HEIGHT = 60;

#define ROW 18
#define COL 32

#include "Unit.hpp"
#include "Drawable.hpp"
#include "Window.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <stack>
#include "cmath"
#include <cstring>

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;
typedef std::pair<std::string, sf::RectangleShape> element;

struct cell
{
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

class Map : public Drawable
{
private:
    int rows;
    int cols;
    std::unordered_map<std::string, sf::RectangleShape> elements;
    sf::Sprite map_sprite;
    sf::Texture map_texture;
    std::vector<std::vector<int>> map_grid;
    std::vector<Pair> directions;

public:
    Map();
    void draw(sf::RenderWindow *window);
    sf::RectangleShape createTower(float x, float y, sf::Color baseColor);

    std::vector<std::vector<int>> &getMapGrid();

    // A* algo
    bool isValid(int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    bool isUnBlocked(int row, int col);
    std::stack<Pair> tracePath(cell cellDetails[][COL], Pair dest);
    std::stack<Pair> aStarSearch(Pair src, Pair dst);
};

#endif // UNITS_HEADER_MAP_HPP_
