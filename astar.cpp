#include <vector>
#include <iostream>
#include <utility>
#include <set>
using namespace std;

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

struct cell
{
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

vector<Pair> directions = {make_pair(0, 1), make_pair(0, -1), make_pair(1, 0), make_pair(-1, 0), make_pair(1, 1), make_pair(1, -1), make_pair(-1, 1), make_pair(-1, -1)};

#define ROW 18
#define COL 32

int grid[ROW][COL] = {
	    //     {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31} 
        /*0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*1*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*2*/  {0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		/*3*/  {0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		/*4*/  {0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		/*5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*6*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*7*/  {0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0},
		/*8*/  {0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0},
		/*9*/  {0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0},
		/*10*/ {0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0},
		/*11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*12*/ {0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		/*13*/ {0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		/*15*/ {0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		/*16*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		/*17*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    };

bool isValid(int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
	// Return using the distance formula
	return ((double)sqrt(
		(row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}


// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (grid[row][col] == 0)
        return (true);
    else
        return (false);
}


// A Utility Function to trace the path from the source
// to destination
void tracePath(cell cellDetails[][COL], Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }

    return;
}

void aStarSearch(Pair src, Pair dst)
{
	if (isValid(src.first, src.second) == false)
	{
		printf("source is invalid\n");
		return;
	}

	if (isValid(dst.first, dst.second) == false)
	{
		printf("dst is invalid\n");
		return;
	}

	// if (isUnBlocked(src.first, src.second) == false)

	if (isDestination(src.first, src.second, dst))
	{
		printf("we are already at the destination\n");
		return;
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

	set<pPair> openList;

	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDst = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;
		double gNew, hNew, fNew;

		for (Pair cur_dir : directions)
		{
			int r = i + cur_dir.first, c = j + cur_dir.second;
			if (isValid(r, c))
			{
				if (isDestination(r, c, dst))
				{
					cellDetails[r][c].parent_i = i;
					cellDetails[r][c].parent_j = j;
					printf("destination is found\n");
					tracePath(cellDetails, dst);
					foundDst = true;
					return;
				}
				else if (closedList[r][c] == false && isUnBlocked(r, c))
				{
					gNew = cellDetails[i][j].g + 1.0;
					hNew = calculateHValue(i - 1, j, dst);
					fNew = gNew + hNew;

					if (cellDetails[r][c].f == __FLT_MAX__ || cellDetails[r][c].f > fNew)
					{
						openList.insert(make_pair(fNew, make_pair(r, c)));

						cellDetails[r][c].f = fNew;
						cellDetails[r][c].f = gNew;
						cellDetails[r][c].f = hNew;
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
	return;
}

int main(void) {
	Pair src = make_pair(8, 0);

    // Destination is the left-most top-most corner
    Pair dest = make_pair(0, 0);

    aStarSearch(src, dest);

	return 0;
}