#include <fstream>
#include <string>
#include <vector>

#define PATH "./input.txt"
//#define PATH "./test_input.txt"

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

Num* findExplode(Num* n, int depth)
{
    if (n->isPair)
    {
        Num* left = findExplode(n->l, depth+1);
        if (left != nullptr) return left;

        printf("[EXPLODE SEARCH] (depth = %i) ", depth);
        n->debug();
        printf("\n");

        if (depth >= 4 && !n->l->isPair && !n->r->isPair)
        {
            return n;
        }

        Num* right = findExplode(n->r, depth+1);
        if (right != nullptr) return right;
    }

    return nullptr;
}
Num* findSplit(Num* n)
{
    if (n->isPair)
    {
        Num* left = findSplit(n->l);
        if (left != nullptr) return left;

        Num* right = findSplit(n->r);
        if (right != nullptr) return right;
    }

    if (!n->isPair && n->val >= 10) return n;

    return nullptr;
}

void explode(Num* n)
{
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

void split(Num* n)
{
    const long left = n->val / 2;
    const long right = (n->val + 1)/ 2;

    n->val = 0;
    n->isPair = true;

    n->l = new Num(left);
    n->l->p = n;
    n->r = new Num(right);
    n->r->p = n;
}

void reduce(Num* n)
{
    //TODO: Explode and split works well
    // Just need to change how we loop through the operations
    // Implement find fonctions instead to find the next explosion and split to do
    Num* nextExplode = findExplode(n, 0);
    if (nextExplode != nullptr)
    {
        printf("[SHOULD EXPLODE] ");
        nextExplode->debug();
        printf("\n");

        explode(nextExplode);
        printf("[DONE EXPLODE] ");
        n->debug();
        printf("\n");

        reduce(n);
        return;
    }

    Num* nextSplit = findSplit(n);
    if (nextSplit != nullptr)
    {
        printf("[SHOULD SPLIT]");
        nextSplit->debug();
        printf("\n");

        split(nextSplit);
        printf("[AFTER SPLIT]");
        n->debug();
        printf("\n");

        reduce(n);
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
        reduce(num);
    }

    return num;
}

unsigned long long calcMagnitude(Num* n)
{
    if (n->isPair)
    {
        return (3 * calcMagnitude(n->l)) + (2 * calcMagnitude(n->r));
    }

    return n->val;
}

int main(int argc, char** argv)
{
    Num* n = buildFromFile(std::ifstream(PATH));
    n->debug();
    printf("\n");

    printf("\nResult = %lld", calcMagnitude(n));
    return 0;
}
