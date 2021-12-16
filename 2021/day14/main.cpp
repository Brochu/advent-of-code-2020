#include <fstream>
#include <map>
#include <string>
#include <vector>

#define PATH "./test_input.txt"
//#define PATH "./input.txt"

#define STEPS 10
#define WINDOW 2

std::map<size_t, char> expandStep(const std::string& start, std::map<std::string, char>& rules)
{
    std::map<size_t, char> queuedInsert;
    size_t offset = 0;

    for (size_t i = 0; (i + WINDOW) < start.size(); i++)
    {
        std::string current;
        for (size_t j = 0; j < WINDOW; j++)
        {
            current += start[i+j];
        }
        //printf("%s, %ld\n", current.c_str(), current.size());

        auto ins = rules[current];
        if (ins != 0)
        {
            queuedInsert[i+1+(offset++)] = ins;
        }
    }

    return queuedInsert;
}

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);
    std::string start;
    std::map<std::string, char> rules;

    std::string line;
    while (getline(file, line))
    {
        if (line.size() <= 1) continue;

        auto idx = line.find('-');
        if (idx != std::string::npos)
            rules[line.substr(0, idx-1)] = line.substr(idx+3)[0];
        else
            start = line;
    }

    printf("[START] %s\n", start.c_str());
    //for (const std::pair<std::string, char>& r : rules)
    //{
    //    printf("[RULE] %s : %c\n", r.first.c_str(), r.second);
    //}

    for (int i = 0; i < STEPS; i++)
    {
        auto inserts = expandStep(start, rules);
        for (const std::pair<size_t, char>& ins : inserts)
        {
            start.insert(ins.first, 1, ins.second);
        }
    }
    printf("[After %i steps] %ld\n", STEPS, start.length());

    std::map<char, size_t> counts;
    for (const char& c : start)
    {
        if (c > 'A')
            counts[c]++;
    }

    size_t min = 1000;
    size_t max = 0;
    for (const std::pair<char, size_t>& p : counts)
    {
        printf("%c - %ld\n", p.first, p.second);
        if (p.second > max)
        {
            max = p.second;
        }
        if (p.second < min)
        {
            min = p.second;
        }
    }

    size_t count = max - min;
    printf("\nmin = %ld, max = %ld, Result = %ld\n", min, max, count);
    return 0;
}
