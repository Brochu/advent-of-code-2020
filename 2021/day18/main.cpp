#include <fstream>
#include <string>
#include <vector>

//#define PATH "./input.txt"
#define PATH "./test_input.txt"

struct Num
{
    bool isPair = false;

    // Pair Type
    Num* p;

    Num* l;
    Num* r;

    // Literal Type
    long val;

    Num(Num* left, Num* right)
        : isPair(true), p(nullptr), l(left), r(right)
    { }

    Num(long value)
        : isPair(false), p(nullptr), val(value)
    { }

    Num()
        : isPair(true), p(nullptr), l(nullptr), r(nullptr)
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

    size_t idx = findSplit(inside);
    std::string lstr = inside.substr(0, idx);
    std::string rstr = inside.substr(idx+1);

    Num* left = buildFromLine(lstr);
    Num* right = buildFromLine(rstr);

    Num* n = new Num(left, right);
    left->p = n;
    right->p = n;

    return n;
}

Num* add(Num* first, Num* second)
{
    Num* n = new Num(first, second);
    first->p = n;
    second->p = n;

    return n;
}

void reduce(Num* n, int depth)
{
    if (n->isPair)
    {
        reduce(n->l, depth+1);
    }

    // My own

    if (n->isPair)
    {
        reduce(n->r, depth+1);
    }
}

Num* buildFromFile(std::ifstream&& file)
{
    std::string line;
    getline(file, line);
    Num* num = buildFromLine(line);

    while(getline(file, line))
    {
        Num* second = buildFromLine(line);
        num = add(num, second);
        reduce(num, 0);
    }

    return num;
}

int main(int argc, char** argv)
{
    Num* n = buildFromFile(std::ifstream(PATH));
    n->debug();
    printf("\n");

    return 0;
}
