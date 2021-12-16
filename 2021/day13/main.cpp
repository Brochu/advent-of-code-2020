#include <fstream>
#include <string>

#define PATH "./test_input.txt"
//#define PATH "./input.txt"

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);

    std::string line;
    while (getline(file, line))
    {
        printf("* %s\n", line.c_str());
    }

    printf("\nResult = \n");
    return 0;
}
