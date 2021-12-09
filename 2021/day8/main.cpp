#include <algorithm>
#include <climits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

int countEasyNums(std::string raw)
{
    printf("%s\n", raw.c_str());
    int count = 0;

    std::stringstream ss(raw);
    std::string current;
    while(std::getline(ss, current, ' '))
    {
        printf("- %s[%ld]\n", current.c_str(), current.length());

        int len = current.length();
        if (len == 2 || len == 3 || len == 4 || len == 7) count++;
    }

    return count;
}

static std::string testPath = "./test_input.txt";
static std::string path = "./input.txt";
int main(int argc, char** argv)
{
    //auto file = std::ifstream(testPath);
    auto file = std::ifstream(path);

    std::string line;
    int quantity = 0;
    while (std::getline(file, line))
    {
        std::string raw = line.substr(line.find('|') + 2);
        quantity += countEasyNums(raw);
    }

    printf("\nResult = %i\n", quantity);
    return 0;
}
