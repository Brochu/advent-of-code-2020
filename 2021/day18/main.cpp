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

    //printf("[LINE] %s\n", inside.c_str());
    size_t idx = findSplit(inside);
    //printf("[IDX] '%ld'\n", idx);

    std::string lstr = inside.substr(0, idx);
    //printf("[LEFT] '%s'\n", lstr.c_str());
    std::string rstr = inside.substr(idx+1);
    //printf("[RIGHT] '%s'\n", rstr.c_str());

    Num* left = buildFromLine(lstr);
    Num* right = buildFromLine(rstr);

    Num* n = new Num(left, right);
    left->p = n;
    right->p = n;

    return n;
}

Num* add(Num* first, Num* second)
{
    return new Num(first, second);
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
    }

    return num;
}

void explode(Num* n)
{
    n->debug();
    printf("\n");

    n->isPair = false;
    n->val = 0;

    long left = n->l->val;
    n->l = nullptr;
    long right = n->r->val;
    n->r = nullptr;

    // Find the left sibling to add the left value
    Num* temp = n->p;
    Num* prev = n;
    while (temp->l == prev)
    {
        prev = temp;
        temp = temp->p;
    }
    temp = temp->l;
    while (temp->isPair)
    {
        temp = temp->r;
    }

    temp->debug();
    printf("\n");

    // Find the right sibling to add the right value
}

void split(Num* n)
{
    //TODO: Split logic, if value > 10, we need to split
}

void reduce(Num* n, int depth)
{
    printf("[REDUCE] depth = %i; current = ", depth);
    n->debug();
    if (depth >= 4 && n->isPair)
    {
        printf(" (EXPLODE)");
    }
    printf("\n");

    if (n->isPair)
    {
        if (depth >= 4)
        {
            explode(n);
        }
        else
        {
            reduce(n->l, depth+1);
            reduce(n->r, depth+1);
        }
    }
}

int main(int argc, char** argv)
{
    Num* n = buildFromFile(std::ifstream(PATH));

    // Parent pointer tests
    //Num* current = n;
    //while (current->isPair)
    //{
    //    current = current->r;
    //}
    //current->debug();
    //printf("\n");

    //while(current->p != nullptr)
    //{
    //    current = current->p;
    //}
    //current->debug();
    //printf("\n");

    // Start reducing the number
    reduce(n, 0);
    //n->debug();
    //printf("\n");

    return 0;
}
