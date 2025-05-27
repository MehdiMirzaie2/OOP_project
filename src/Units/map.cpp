#include "../../include/map.hpp"

// background image width = 960
// background image height = 540
// cells 30 x 30

Map::Map()
{

    m_map_grid = {
        //     {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31} 
        /*0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*1*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*2*/  {0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0},
		/*3*/  {0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0},
		/*4*/  {0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0},
		/*5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*6*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*8*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*10*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*12*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*13*/ {0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0},
		/*14*/ {0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0},
		/*15*/ {0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0},
		/*16*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*17*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    };


    //directions = {std::make_pair(0, -1), std::make_pair(1, 0), std::make_pair(0, 1), std::make_pair(-1, 0)};
    m_directions = {std::make_pair(0, 1), std::make_pair(0, -1), std::make_pair(1, 0), std::make_pair(-1, 0), std::make_pair(1, 1), std::make_pair(1, -1), std::make_pair(-1, 1), std::make_pair(-1, -1)};
    //map background set up
    if(!m_map_texture.loadFromFile("src/Textures/background.png")){
		std:: cout << "COULDNT FIND THE MAP BG\n";
	}
	
    m_map_sprite.setTexture(m_map_texture);
	m_map_sprite.setOrigin(m_map_texture.getSize().x/2.f, m_map_texture.getSize().y/2.f);

    
	m_map_sprite.setPosition(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);
	// flip the map, colours are opposite in the png
	m_map_sprite.setScale(-1.f, 1.f);


    // Towers (up to down, in order)
    // auto enemyKing = createTower(WINDOW_WIDTH / 2.9 - TOWER_WIDTH / 1, WINDOW_HEIGHT / 3, sf::Color::Red); // 2
    auto enemyLeftPrincess = createTower(WINDOW_WIDTH / 3 - 300, 80, sf::Color::Red);                      // 3
    auto enemyRightPrincess = createTower(WINDOW_WIDTH / 3 + 149, 80, sf::Color::Red);                     // 1

    // auto playerKing = createTower(WINDOW_WIDTH / 2.9 - TOWER_WIDTH / 1, WINDOW_HEIGHT + 45, sf::Color::Blue); // 2
    auto playerLeftPrincess = createTower(WINDOW_WIDTH / 3 - 300, WINDOW_HEIGHT + 232, sf::Color::Blue);      // 3
    auto playerRightPrincess = createTower(WINDOW_WIDTH / 3 + 149, WINDOW_HEIGHT + 232, sf::Color::Blue);     // 1
}

sf::RectangleShape Map::createTower(float x, float y, sf::Color baseColor)
{
    sf::RectangleShape tower(sf::Vector2f(TOWER_WIDTH, TOWER_HEIGHT));
    tower.setPosition(y, WINDOW_HEIGHT - x - TOWER_WIDTH);
    tower.setFillColor(baseColor);
    tower.setOutlineThickness(2);
    tower.setOutlineColor(sf::Color::Black);
    return tower;
}



void Map::draw(sf::RenderWindow *window)
{
    // std::cout << "hello world\n";
    if (m_map_sprite.getTexture() == NULL)
        std::cout << "there is no texture " << m_map_sprite.getPosition().x << std::endl;

    window->draw(m_map_sprite);

}

// Background


std::vector<std::vector<int>> &Map::getMapGrid() {
    return m_map_grid;
}

bool Map::isValid(int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool Map::isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double Map::calculateHValue(int row, int col, Pair dest)
{
	//return abs(row - dest.first) + abs(col - dest.second);
	// Return using the distance formula
	return ((double)sqrtf(
		(row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}


// A Utility Function to check whether the given cell is
// blocked or not
bool Map::isUnBlocked(int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (m_map_grid[row][col] == 0)
        return (true);
    else
        return (false);
}


// A Utility Function to trace the path from the source
// to destination
std::stack<Pair> Map::tracePath(cell cellDetails[][COL], Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(std::make_pair(row, col));
    std::stack<Pair> temp = Path;
    while (!temp.empty()) {
         Pair p = temp.top();
         temp.pop();
         printf("-> (%d,%d) ", p.first, p.second);
     }
    return Path;
}

std::stack<Pair> Map::aStarSearch(Pair src, Pair dst)
{
	if (isValid(src.first, src.second) == false)
	{
		printf("source is invalid\n");
		return {};
	}

	if (isValid(dst.first, dst.second) == false)
	{
		printf("dst is invalid\n");
		return {};
	}

	if (isUnBlocked(src.first, src.second) == false 
		|| isUnBlocked(dst.first, dst.second) == false) {
		printf("source or dest is blocked\n");
	}

	if (isDestination(src.first, src.second, dst))
	{
		printf("we are already at the destination\n");
		return {};
	}

	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	cell cellDetails[ROW][COL];

	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			cellDetails[i][j].f = __FLT_MAX__;
			cellDetails[i][j].g = __FLT_MAX__;
			cellDetails[i][j].h = __FLT_MAX__;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0f;
	cellDetails[i][j].g = 0.0f;
	cellDetails[i][j].h = 0.0f;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	std::set<pPair> openList;

	openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

	bool foundDst = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;
		double gNew, hNew, fNew;

		for (Pair cur_dir : m_directions)
		{
			int r = i + cur_dir.first, c = j + cur_dir.second;
			if (isValid(r, c))
			{
				if (isDestination(r, c, dst))
				{
					cellDetails[r][c].parent_i = i;
					cellDetails[r][c].parent_j = j;
					printf("destination is found\n");
					
					// foundDst = true;
					return tracePath(cellDetails, dst);;
				}
				else if (closedList[r][c] == false && isUnBlocked(r, c))
				{
					gNew = cellDetails[i][j].g + 1.0;
					hNew = calculateHValue(r, c, dst);
					fNew = gNew + hNew;

					if (cellDetails[r][c].f == __FLT_MAX__ || cellDetails[r][c].f > fNew)
					{
						openList.insert(std::make_pair(fNew, std::make_pair(r, c)));

						cellDetails[r][c].f = fNew;
						cellDetails[r][c].g = gNew;
						cellDetails[r][c].h = hNew;
						cellDetails[r][c].parent_i = i;
						cellDetails[r][c].parent_j = j;
					}
				}
			}
		}
	}
	if (foundDst == false)
	{
		printf("failed to find the destination cell\n");
	}
	return {};
}
