#include <algorithm>
#include <climits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

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
    std::vector<std::string> hints;
    std::vector<std::string> nums;
};
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

    parseList(raw.substr(0, idx), e.hints);
    std::sort(e.hints.begin(), e.hints.end(), [](const std::string& l, const std::string& r)
    {
        return l.length() < r.length();
    });
    parseList(raw.substr(idx + 2), e.nums);

    return e;
}

int calcNums(const Entry& e)
{
    printf("[Calc] -> \n");
    printf("hints: ");
    auto eight = e.hints.back();
    auto seven = *(++(e.hints.begin()));
    printf(" %s , %s ", eight.c_str(), seven.c_str());
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

        nums.push_back(calcNums(parseEntry(line)));
    }

    printf("\nResult = %i\n", std::accumulate(nums.cbegin(), nums.cend(), 0));
    return 0;
}
