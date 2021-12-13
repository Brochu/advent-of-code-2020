#include <algorithm>
#include <fstream>
#include <set>
#include <string>
#include <vector>

typedef std::pair<short, short> Coords;
typedef std::set<Coords> FlashCache;
typedef std::vector<Coords> FlashList;

#define PATH "./test_input.txt"
//#define PATH "./input.txt"

#define STEPS 1
#define DIM 5
static short jellies[DIM][DIM];

void debugJellies()
{
    printf("---------------\n");
    for (int y = 0; y < DIM; y++)
    {
        for (int x = 0; x < DIM; x++)
        {
            printf(" %i ", jellies[y][x]);
        }
        printf("\n");
    }
}

std::vector<Coords> generateNeighbors(Coords c)
{
    std::vector<Coords> coords;

    short y = std::get<0>(c);
    short x = std::get<1>(c);

    for (short i = -1; i <= 1; i++)
    {
        for (short j = -1; j <= 1; j++)
        {
            if (i != 0 || j != 0)
            {
                short newY = y + i;
                short newX = x + j;

                if (newY < 10 && newY >= 0 && newX < 10 && newX >= 0)
                    coords.push_back(std::make_pair(newY, newX));
            }
        }
    }

    return coords;
}

FlashList incrementJellies()
{
    std::vector<Coords> updateList;

    for (int y = 0; y < DIM; y++)
    {
        for (int x = 0; x < DIM; x++)
        {
            jellies[y][x]++;
            if (jellies[y][x] == 10) updateList.push_back(std::make_pair(y, x));
        }
    }

    return updateList;
}

void handleFlashes(FlashList& toFlash, size_t idx, FlashCache& cache)
{
    const Coords c = toFlash[idx];
    const short y = std::get<0>(c);
    const short x = std::get<1>(c);

    printf("[FLASH] Handling idx = %ld; (%i, %i); %i\n", idx, y, x, jellies[y][x]);

    //TODO: find a way to propagate the flashes, most likely keep adding the new ones to flash to the list ?
    if (jellies[y][x] > 9)
    {
        jellies[y][x] -= 10;
    }
}

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);

    std::string line;

    short y = 0;
    while (file >> line)
    {
        for (int x = 0; x < DIM; x++)
        {
            jellies[y][x] = line[x] - '0';
        }
        y++;
    }

    debugJellies();
    for (int i = 0; i < STEPS; i++)
    {
        FlashCache cache;
        FlashList toFlash = incrementJellies();
        printf("With %ld to update...\n", toFlash.size());

        for (size_t i = 0; i < toFlash.size(); i++)
        {
            handleFlashes(toFlash, i, cache);
        }
    }
    debugJellies();

    return 0;
}
