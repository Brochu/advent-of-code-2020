#include <algorithm>
#include <climits>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

int countEasyNums(std::string raw)
{
    //printf("%s\n", raw.c_str());
    int count = 0;

    std::stringstream ss(raw);
    std::string current;
    while(std::getline(ss, current, ' '))
    {
        //printf("- %s[%ld]\n", current.c_str(), current.length());

        int len = current.length();
        if (len == 2 || len == 3 || len == 4 || len == 7) count++;
    }

    return count;
}

struct Entry
{
    std::unordered_map<int, std::vector<std::string>> hints;
    std::vector<std::string> nums;
};
void parseHints(const std::string& raw, std::unordered_map<int, std::vector<std::string>>& table)
{
    std::stringstream ss(raw);
    std::string current;

    while(std::getline(ss, current, ' '))
    {
        table[current.length()].push_back(current);
    }
}
void parseList(const std::string& raw, std::vector<std::string>& destination)
{
    std::stringstream ss(raw);
    std::string current;

    while(std::getline(ss, current, ' '))
    {
        destination.push_back(current);
    }
}
Entry parseEntry(std::string raw)
{
    Entry e;
    size_t idx = raw.find('|');

    parseHints(raw.substr(0, idx), e.hints);
    //std::sort(e.hints.begin(), e.hints.end(), [](const std::string& l, const std::string& r)
    //{
    //    return l.length() < r.length();
    //});
    parseList(raw.substr(idx + 2), e.nums);

    return e;
}

void findSixSegments(
    std::vector<std::string> potentials,
    const std::vector<std::string>& known,
    std::string& outSix,
    std::string& outNine,
    std::string& outZero
)
{
    auto it = potentials.begin();
    for(; it != potentials.end(); it++)
    {
        for(const char& c : known[7])
        {
            if ((*it).find(c) == std::string::npos)
            {
                outSix = *it;
                break;
            }
        }
    }
    potentials.erase(it);
}

int calcNums(Entry& e)
{
    printf("[Calc] -> \n");
    printf("hints: ");
    // KNOWN
    std::vector<std::string> known(10);

    auto eight = e.hints.at(7).front();
    std::sort(eight.begin(), eight.end());
    known[8] = eight;

    auto one = e.hints.at(2).front();
    std::sort(one.begin(), one.end());
    known[1] = one;

    auto four = e.hints.at(4).front();
    std::sort(four.begin(), four.end());
    known[4] = four;

    auto seven = e.hints.at(3).front();
    std::sort(seven.begin(), seven.end());
    known[7] = seven;
    printf("8->%s; 1->%s; 4->%s; 7->%s", eight.c_str(), one.c_str(), four.c_str(), seven.c_str());

    // 6 segments unknown
    printf("\nFind zero, six, nine\n");
    std::string six;
    std::string nine;
    std::string zero;
    findSixSegments(e.hints[6], known, six, nine, zero);
    printf("6->%s; 9->%s; 0->%s\n", six.c_str(), nine.c_str(), zero.c_str());

    printf("\nFind two, three, five\n");
    for(const std::string& s : e.hints.at(5))
    {
        printf("%s ; ", s.c_str());
    }
    printf("\n");

    //printf("nums: ");
    //for(const std::string& n : e.nums)
    //{
    //    printf("%s,", n.c_str());
    //}
    //printf("\n");

    return 0;
}

static std::string testPath = "./test_input.txt";
static std::string path = "./input.txt";
int main(int argc, char** argv)
{
    auto file = std::ifstream(testPath);
    //auto file = std::ifstream(path);

    std::vector<int> nums;
    std::string line;
    int quantity = 0;
    std::getline(file, line);
    //while (std::getline(file, line))
    {
        std::string raw = line.substr(line.find('|') + 2);
        quantity += countEasyNums(raw);

        Entry e = parseEntry(line);
        nums.push_back(calcNums(e));
    }

    //printf("\nResult = %i\n", std::accumulate(nums.cbegin(), nums.cend(), 0));
    return 0;
}
