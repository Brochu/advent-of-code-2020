#include <fstream>
#include <string>

#define PATH "./test_input.txt"
//#define PATH "./input.txt"

int main(int argc, char** argv)
{
    std::ifstream file = std::ifstream(PATH);

    printf("\nResult = %ld\n", 0L);
    return 0;
}
