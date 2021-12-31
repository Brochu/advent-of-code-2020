#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//#define PATH "./input.txt"
#define PATH "./test_input.txt"

struct Beacon
{
    long x;
    long y;
    long z;

    std::string toString() const
    {
        std::string out;
        sprintf(&out[0], "{%ld, %ld, %ld}", x, y, z);
        return out;
    }
};

struct Scanner
{
    std::vector<Beacon> beacons;

    Scanner(){}
    Scanner(std::vector<std::string> lines)
    {
        for (int i = 1; i < lines.size(); i++)
        {
            std::stringstream ss(lines[i]);

            long x;
            ss >> x;
            ss.ignore(1);

            long y;
            ss >> y;
            ss.ignore(1);

            long z;
            ss >> z;

            beacons.push_back(Beacon { x, y, z });
        }
    }

    void debug() const
    {
        for (const auto& b : beacons)
        {
            printf("* %s\n", b.toString().c_str());
        }
        printf("\n");
    }
};

std::vector<Scanner> parseFile(std::ifstream&& file)
{
    std::vector<Scanner> results;

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line))
    {
        if (line.size() > 0)
        {
            lines.push_back(line);
        }
        else if (line.size() <= 0)
        {
            results.push_back(Scanner(lines));
            lines.clear();
        }
    }

    results.push_back(Scanner(lines));
    lines.clear();

    return results;
}

int main(int argc, char** argv)
{
    std::vector<Scanner> scans = parseFile(std::ifstream(PATH));
    for (const Scanner& s : scans)
    {
        s.debug();
    }

    return 0;
}
