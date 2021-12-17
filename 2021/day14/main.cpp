#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>

//#define PATH "./test_input.txt"
#define PATH "./input.txt"

#define STEPS 20
#define WINDOW 2

std::map<size_t, char> expandStep(const std::string& start, std::map<std::string, char>& rules, std::vector<size_t>& counts)
{
    std::map<size_t, char> queuedInsert;
    int offset = 0;

    for (int i = 0; (i + WINDOW-1) < start.size(); i++)
    {
        std::string current;
        for (int j = 0; j < WINDOW; j++)
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

    printf("[START][%ld] '%s'\n", start.length(), start.c_str());
    //for (const std::pair<std::string, char>& r : rules)
    //{
    //    printf("[RULE] %s : %c\n", r.first.c_str(), r.second);
    //}

    std::vector<size_t> counts(26, 0);
    for (const char& c : start)
    {
        if (c >= 'A')
            counts[c - 'A']++;
    }

    for (int i = 0; i < STEPS; i++)
    {
        auto inserts = expandStep(start, rules, counts);
        for (const std::pair<size_t, char>& ins : inserts)
        {
            start.insert(ins.first, 1, ins.second);
            counts[ins.second - 'A']++;
        }

        printf("[step %i][%ld]\n", i, start.length());
    }

    //auto end = std::remove_if(counts.begin(), counts.end(), [](const size_t& e){ return e <= 0; });
    //auto minmax = std::minmax_element(counts.begin(), end);
    //printf("min = %ld; max = %ld\n", *minmax.first, *minmax.second);

    //size_t count = *minmax.second - *minmax.first;
    //printf("\nResult = %ld\n", count);
    return 0;
}
