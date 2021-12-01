#include <string>
#include <fstream>
#include <vector>
#include <set>

class Day9
{
public:
    Day9(char* fname) : filename(fname)
    { }

    void init_from_file()
    {
        std::ifstream file(filename);
        std::string line;
        while(file)
        {
            std::getline(file, line);
            _nums.push_back(atoi(line.c_str()));
        }

        file.close();
    }

    void init_from_debug(const std::vector<int>& nums)
    {
        _nums = std::vector<int>(nums);
    }
    
    int check_d1(int preamble) const
    {
        std::set<int> window;
        for(int i = 0; i < preamble; ++i)
        {
            window.insert(_nums[i]);
        }
        
        int low = 0;
        int high = preamble-1;
        int check = preamble;

        while(check < _nums.size())
        {
            if (check_valid(window, _nums[check]))
            {
                ++check;
                window.erase(_nums[low++]);
                window.insert(_nums[++high]);
            }
            else
            {
                return _nums[check];
            }
        }

        return -1;
    }

    bool check_valid(const std::set<int>& window, int to_check) const
    {
        for(const int& num : window)
        {
            int t = to_check - num;
            if (window.find(t) != window.cend()) return true;
        }

        return false;
    }

    std::vector<int> check_d2(int to_check) const
    {
        int low = 0;
        int high = 0;
        int subtotal = _nums[0];

        while(subtotal < to_check)
        {
            subtotal += _nums[++high];
        }

        while(subtotal != to_check && high < _nums.size())
        {
            if (subtotal < to_check)
            {
                subtotal += _nums[++high];
            }
            else if (subtotal > to_check)
            {
                subtotal -= _nums[low++];
            }
        }

        if (subtotal == to_check)
        {
            return std::vector<int>(_nums.begin()+low, _nums.begin()+(high+1));
        }
        else
        {
            return std::vector<int>();
        }
    }

private:
    std::string filename;
    std::vector<int> _nums;
};
