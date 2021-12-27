#include <fstream>
#include <string>
#include <vector>

#define PATH "./input.txt"
//#define PATH "./test_input.txt"

struct Num
{
    bool isPair = false;

    // Pair Type
    Num* l;
    Num* r;

    // Literal Type
    long val;

    Num(Num* left, Num* right)
        : isPair(true), l(left), r(right)
    { }

    Num(long value)
        : isPair(false), val(value)
    { }

    Num()
        : isPair(true), l(nullptr), r(nullptr)
    { }

    ~Num()
    {
        delete l;
        delete r;
    }

    void debug()
    {
        if (!isPair)
        {
            printf("%ld", val);
        }
        else
        {
            printf("[");
            l->debug();
            printf(",");
            r->debug();
            printf("]");
        }
    }
};

size_t findSplit(const std::string& line)
{
    size_t splitIdx = std::string::npos;
    size_t stack = 0;

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '[') stack++;
        else if (line[i] == ']') stack--;

        if (line[i] == ',' && stack == 0)
        {
            splitIdx = i;
            break;
        }
    }

    return splitIdx;
}

Num* buildFromLine(const std::string& line)
{
    if (line[0] != '[')
    {
        auto val = atoi(line.c_str());
        return new Num(val);
    }

    const std::string inside(++line.begin(), --line.end());

    //printf("[LINE] %s\n", inside.c_str());
    size_t idx = findSplit(inside);
    //printf("[IDX] '%ld'\n", idx);

    std::string lstr = inside.substr(0, idx);
    //printf("[LEFT] '%s'\n", lstr.c_str());
    std::string rstr = inside.substr(idx+1);
    //printf("[RIGHT] '%s'\n", rstr.c_str());

    Num* left = buildFromLine(lstr);
    Num* right = buildFromLine(rstr);

    return new Num(left, right);
}

Num* buildFromFile(std::ifstream&& file)
{
    std::string line;
    getline(file, line);

    printf("%s\n", line.c_str());
    return buildFromLine(line);
}

int main(int argc, char** argv)
{
    Num* n = buildFromFile(std::ifstream(PATH));
    n->debug();

    return 0;
}
