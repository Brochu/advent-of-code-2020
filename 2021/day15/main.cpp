#include <array>
#include <fstream>
#include <math.h>
#include <queue>
#include <string>

#define PATH "./test_input.txt"
//#define PATH "./input.txt"
#define DIM 10

typedef std::array<std::array<short, DIM>, DIM> Grid;
typedef std::pair<int, int> Coord;

struct Node
{
    Coord c;
    int val;
};

Grid parseGrid(std::ifstream& file)
{
    Grid g;

    std::string line;
    short y = 0;
    while (getline(file, line))
    {
        for (short x = 0; x < line.length(); x++)
            g[y][x] = line[x] - '0';

        y++;
    }

    return g;
}

int dijkstra(const Grid& grid, const Coord& start, const Coord& end)
{
    //TODO: Create priority queue with custom comparer
    std::array<std::array<int, DIM>, DIM> dist;
    std::array<std::array<short*, DIM>, DIM> prev;
    return 0;
}

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);
    Grid grid = parseGrid(file);

    //for (int i = 0; i < DIM; i++)
    //{
    //    for (int j = 0; j < DIM; j++)
    //    {
    //        printf("%i ", grid[i][j]);
    //    }
    //    printf("\n");
    //}

    int risk = dijkstra(grid, std::make_pair(0, 0), std::make_pair(9, 9));

    printf("\nResult = %i\n", risk);
    return 0;
}
