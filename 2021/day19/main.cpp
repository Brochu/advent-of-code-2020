#include <fstream>
#include <string>
#include <vector>

//#define PATH "./input.txt"
#define PATH "./test_input.txt"

void parseFile(std::ifstream&& file)
{
    std::string line;
    while (getline(file, line))
    {
        printf("* %s\n", line.c_str());
    }
}

int main(int argc, char** argv)
{
    parseFile(std::ifstream(PATH));
    return 0;
}
