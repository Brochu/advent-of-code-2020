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

bool shouldExplode(Num* n, int depth)
{
    if (n->isPair)
    {
        const bool validPair = !n->l->isPair && !n->r->isPair;
        return validPair && depth >= 4;
    }

    return false;
}
bool shouldSplit(Num* n, int depth)
{
    return !n->isPair && n->val >= 10;
}

// Forward declare here since we need some recursion...
void explode(Num* n, int depth)
{
    // Add each of values to nearest normal values (left and right)
    // Change current n to a zero node

    const long left = n->l->val;
    const long right = n->r->val;

    n->l = nullptr;
    delete n->l;
    n->r = nullptr;
    delete n->r;
    n->isPair = false;
    n->val = 0;

    Num* temp = n->p;
    Num* prev = n;
    while (temp != nullptr && temp->l == prev)
    {
        prev = temp;
        temp = temp->p;
    }
    if (temp != nullptr)
    {
        temp = temp->l;
        while (temp->isPair)
        {
            temp = temp->r;
        }
        temp->val += left;
    }

    temp = n->p;
    prev = n;
    while (temp != nullptr && temp->r == prev)
    {
        prev = temp;
        temp = temp->p;
    }
    if (temp != nullptr)
    {
        temp = temp->r;
        while (temp->isPair)
        {
            temp = temp->l;
        }
        temp->val += right;
    }
}

void split(Num* n, int depth)
{
    const long left = n->val / 2;
    const long right = (n->val + 1)/ 2;
    printf("\n[SPLIT] l = %ld; r = %ld", left, right);

    n->val = 0;
    n->isPair = true;

    n->l = new Num(left);
    n->l->p = n;
    n->r = new Num(right);
    n->r->p = n;
}

long reduce(Num* n, int depth)
{
    long count = 0;
    // Deal with left element
    if (n->isPair)
    {
        count += reduce(n->l, depth+1);
    }

    printf("[depth = %i] ", depth);
    n->debug();
    if (shouldExplode(n, depth))
    {
        printf(" (EXPLODE)");
        explode(n, depth);
        count++;
    }
    else if (shouldSplit(n, depth))
    {
        printf(" (SPLIT)");
        split(n, depth);
        count++;
    }
    printf("\n");

    // Deal with right element
    if (n->isPair)
    {
        count += reduce(n->r, depth+1);
    }

    return count;
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

        long count = reduce(num, 0);
        while (count != 0)
        {
            count = reduce(num, 0);
        }
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
