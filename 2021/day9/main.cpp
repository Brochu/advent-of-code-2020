#include <algorithm>
#include <climits>
#include <fstream>
#include <math.h>
#include <numeric>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

char getFieldValue(std::vector<std::vector<char>>& field, int y, int x)
{
    if (y < 0 || y > field.size()) return 0;
    else if (x < 0 || x > field[0].size()) return 0;
    else return field[y][x];
}

#define PATH "./test_input.txt"
//#define PATH "./input.txt"

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);

    std::vector<std::vector<char>> field;
    std::string line;

    int y = 0;
    while (std::getline(file, line))
    {
        printf("Line = %s\n", line.c_str());

        for (int i = 0; i < line.length(); i++)
        {
            if (i == 0) field.push_back(std::vector<char>(line.length()));
            field[y][i] = line[i];
        }

        y++;
    }

    return 0;
}
