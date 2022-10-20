#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

class Day10
{
public:
    Day10(char* fname) : filename(fname)
    { }

    void init_from_file()
    {
        std::ifstream file(filename);
        std::string line;
        while(file)
        {
            std::getline(file, line);
            _adapters.push_back(atoi(line.c_str()));
        }
        file.close();

        std::sort(_adapters.begin(), _adapters.end());
    }
    
    void init_from_debug()
    {
        //_adapters = { 16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4 };
        _adapters = { 0, 28, 33, 18, 42, 31, 14, 46, 20, 48, 47, 24, 23, 49, 45, 19, 38, 39, 11, 1, 32, 25, 35, 8, 17, 7, 9, 4, 2, 34, 10, 3 };
        std::sort(_adapters.begin(), _adapters.end());
        
        for(const int i : _adapters)
        {
            printf("%i, ", i);
        }
        printf("\n");
    }

    int calculate_part1() const
    {
        std::map<int, int> _found;

        int previous = 0;
        for(const int v : _adapters)
        {
            int diff = v - previous;
            _found[diff]++;

            previous = v;
        }
        _found[3]++;
        
        return _found[1] * _found[3];
    }

    long long calculate_part2(int offset = 0)
    {
        const int offset_cache = offset;
        if (_memo.find(offset_cache) != _memo.end()) return _memo[offset_cache];
        const int target = _adapters[offset]+3;
        
        ++offset;
        if (offset >= _adapters.size())
        {
            return 1;
        }
        
        long long total = 0;
        while(offset < _adapters.size() && _adapters[offset] <= target)
        {
            total += calculate_part2(offset);
            ++offset;
        }

        _memo[offset_cache] = total;
        return total;
    }

private:
    std::string filename;
    std::vector<int> _adapters;

    std::map<int, long long> _memo;
};
