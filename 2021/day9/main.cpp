#include <algorithm>
#include <climits>
#include <fstream>
#include <math.h>
#include <numeric>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

static std::string testPath = "./test_input.txt";
static std::string path = "./input.txt";
int main(int argc, char** argv)
{
    auto file = std::ifstream(testPath);
    //auto file = std::ifstream(path);

    std::string line;
    while (std::getline(file, line))
    {
        printf("Line = %s\n", line.c_str());
    }

    return 0;
}
