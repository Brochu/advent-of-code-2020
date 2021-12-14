#include <fstream>
#include <string>
#include <vector>

#define PATH "./test_input.txt"
//#define PATH "./input.txt"

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);

    std::string line;
    while (file >> line)
    {
        printf("* %s\n", line.c_str());
    }

    printf("Result = %i\n", 0);
    return 0;
}
