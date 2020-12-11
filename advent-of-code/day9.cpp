#include <string>
#include <fstream>
#include <vector>
#include <set>

class Day9
{
public:
    Day9(char* fname) : filename(fname)
    { }

    int check_d1_file(int preamble)
    {
        std::vector<int> list;
        
        std::ifstream file(filename);
        std::string line;
        while(file)
        {
            std::getline(file, line);
            list.push_back(atoi(line.c_str()));
        }

        file.close();
        return check_d1_debug(list, preamble);
    }
    
    int check_d1_debug(const std::vector<int>& list, int preamble) const
    {
        std::set<int> window;
        for(int i = 0; i < preamble; ++i)
        {
            window.insert(list[i]);
        }
        
        int low = 0;
        int high = preamble-1;
        int check = preamble;

        while(check < list.size())
        {
            if (check_valid(window, list[check]))
            {
                ++check;
                window.erase(list[low++]);
                window.insert(list[++high]);
            }
            else
            {
                return list[check];
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

private:
    std::string filename;
};
