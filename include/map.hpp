#ifndef UNITS_HEADER_MAP_HPP_
#define UNITS_HEADER_MAP_HPP_

// Constants (swapped for rotation)
const int TOWER_WIDTH = 90;  // Width of tower rectangle
const int TOWER_HEIGHT = 60; // Height of tower rectangle

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

typedef std::pair<int, int> Pair; // Represents grid coordinates
typedef std::pair<double, std::pair<int, int>> pPair; // For A* priority queue: f-value + coordinates
typedef std::pair<std::string, sf::RectangleShape> element; // Pairing a string with a rectangle shape

struct cell
{
    int parent_i, parent_j; // Parent cell coordinates for path reconstruction
    double f, g, h;         // A* cost values: f = g + h
};

class Map
{
private:
    int m_rows; // Number of rows in the grid
    int m_cols; // Number of columns in the grid
    sf::Sprite m_map_sprite; // Sprite representing the map
    sf::Texture m_map_texture; // Texture applied to the map sprite
    std::vector<std::vector<int>> m_map_grid; // 2D grid representing the map layout
    std::vector<Pair> m_directions; // Possible movement directions on the grid

public:
    Map(); // Constructor initializes the map grid and assets
    void draw(sf::RenderWindow *window); // Draws the map to the window
    
    sf::RectangleShape createTower(float x, float y, sf::Color baseColor); // Creates a tower rectangle shape at specified position
    std::vector<std::vector<int>> &getMapGrid(); // Returns a reference to the map grid

    // A* algorithm helper functions
    bool isValid(int row, int col); // Checks if a cell is within map bounds
    bool isDestination(int row, int col, Pair dest); // Checks if cell is the destination
    double calculateHValue(int row, int col, Pair dest); // Heuristic function for A*
    bool isUnBlocked(int row, int col); // Checks if a cell is traversable
    std::stack<Pair> tracePath(cell cellDetails[][COL], Pair dest); // Reconstructs the path from destination to source
    std::stack<Pair> aStarSearch(Pair src, Pair dst); // Performs A* pathfinding from src to dst
};

#endif // UNITS_HEADER_MAP_HPP_
