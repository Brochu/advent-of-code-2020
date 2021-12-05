#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
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
    }

    return 0;
}
