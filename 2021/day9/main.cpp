#include <algorithm>
#include <climits>
#include <fstream>
#include <math.h>
#include <numeric>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

short getFieldValue(std::vector<std::vector<char>>& field, int y, int x)
{
    if (y < 0 || y > field.size()-1) return 10;
    else if (x < 0 || x > field[0].size()) return 10;
    else return field[y][x] - '0';
}

//#define PATH "./test_input.txt"
#define PATH "./input.txt"

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);

    std::vector<std::vector<char>> field;
    std::vector<std::vector<int>> preCheck;
    std::string line;

    int j = 0;
    while (file >> line)
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (i == 0) field.push_back(std::vector<char>(line.length()));
            field[j][i] = line[i];

            if (i == 0) preCheck.push_back(std::vector<int>());

            short minone = (i == 0) ? 10 : line[i-1] - '0';
            short addone = (i == line.size() - 1) ? 10 : line[i+1] - '0';
            short val = line[i] - '0';
            //printf("%i : %i : %i\n", minone, val, addone);

            if (val < minone && val < addone) preCheck[j].push_back(i);
        }
        //printf("\n");

        j++;
    }

    int sum = 0;
    for (int y = 0; y < field.size(); y++)
    {
        for (int x = 0; x < preCheck[y].size(); x++)
        {
            short minone = getFieldValue(field, y-1, preCheck[y][x]);
            short addone = getFieldValue(field, y+1, preCheck[y][x]);
            short val = getFieldValue(field, y, preCheck[y][x]);

            printf("%i : %i : %i \n", minone, val, addone);
            if (val < minone && val < addone) sum += (val+1);
        }
        printf("\n");
    }

    printf("Final = %i\n", sum);

    return 0;
}
