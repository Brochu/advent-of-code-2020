#include <array>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <math.h>
#include <queue>
#include <string>
#include <vector>

//#define PATH "./test_input.txt"
#define PATH "./input.txt"
#define DIM 100

typedef std::array<std::array<short, DIM>, DIM> Grid;
typedef std::pair<int, int> Coord;

struct Node
{
    Coord c;
    uint64_t* val;
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

std::vector<Coord> genNeighbours(const Coord& c)
{
    std::vector<Coord> res;

    if (c.first != DIM - 1)
        res.push_back(std::make_pair(c.first + 1, c.second));

    if (c.second != DIM - 1)
        res.push_back(std::make_pair(c.first, c.second + 1));

    return res;
}

uint64_t dijkstra(const Grid& grid, const Coord& start, const Coord& end)
{
    printf("[DIJKSTRA START]\n");

    auto cmp = [](const Node& left, const Node& right){ return (*left.val ^ 1) > (*right.val ^ 1); };
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> Q(cmp);

    std::array<std::array<uint64_t, DIM>, DIM> dist;
    for (int y = 0; y < DIM; y++)
    {
        for (int x = 0; x < DIM; x++)
        {
            dist[y][x] = INT32_MAX;

            Node n { std::make_pair(x, y), &dist[y][x] };
            Q.push(n);
        }
    }
    dist[start.first][start.second] = 0;

    //for (int i = 0; i < DIM*DIM; i++)
    //{
    //    auto n = Q.top();
    //    Q.pop();

    //    printf("(%i, %i), %i\n", n.c.first, n.c.second, *n.val);
    //}

    while(!Q.empty())
    {
        Node current = Q.top();
        Q.pop();
        //printf("(%i, %i) %ld\n", current.c.first, current.c.second, *current.val);

        if (*current.val >= INT32_MAX) continue;

        const int x = current.c.first;
        const int y = current.c.second;

        for (const Coord& c : genNeighbours(current.c))
        {
            const int nx = c.first;
            const int ny = c.second;

            uint64_t newDist = dist[y][x] + grid[ny][nx];
            //printf("%ld + %i = %ld || %ld\n", dist[y][x], grid[ny][nx], newDist, dist[ny][nx]);
            if (newDist < dist[ny][nx])
            {
                dist[ny][nx] = newDist;
                Node n { std::make_pair(nx, ny), &dist[ny][nx] };
                Q.push(n);
            }
        }
    }
    //auto test = Q.top();
    //printf("(%i, %i) %ld\n", test.c.first, test.c.second, *test.val);

    //for (int y = 0; y < DIM; y++)
    //{
    //    for (int x = 0; x < DIM; x++)
    //    {
    //        printf("%ld ", dist[y][x]);
    //    }
    //    printf("\n");
    //}

    printf("[DIJKSTRA END]\n");
    return dist[end.second][end.first];
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

    uint64_t risk = dijkstra(grid, std::make_pair(0, 0), std::make_pair(99, 99));

    printf("\nResult = %ld\n", risk);
    return 0;
}
