#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

class Day11
{
public:
    Day11(char* fname) : filename(fname)
    {
        //init_from_file();
        init_from_debug();
    }

    void init_from_file()
    {
    }
    
    void init_from_debug()
    {
        std::string input = "L.LL.LL.LL\nLLLLLLL.LL\nL.L.L..L..\nLLLL.LL.LL\nL.LL.LL.LL\nL.LLLLL.LL\n..L.L.....\nLLLLLLLLLL\nL.LLLLLL.L\nL.LLLLL.LL\n";
        
        std::stringstream ss(input);
        std::string line;
        while(ss)
        {
            std::getline(ss, line);
            _map.emplace_back();
            
            std::vector<char>& current_list = _map[_map.size()-1];
            for(const char& c : line)
            {
                current_list.push_back(c);
            }
        }
    }

    void output_map() const
    {
        for(int i = 0; i < _map.size(); ++i)
        {
            for(int j = 0; j < _map[i].size(); ++j)
            {
                printf(" %c ", _map[i][j]);
            }
            printf("\n");
        }
    }

    bool is_valid(const std::pair<int, int>& p) const
    {
        const int& x = std::get<0>(p);
        const int& y = std::get<1>(p);

        return (x >= 0 && x < _map.size()) && (y >= 0 && y < _map[x].size());
    }
    bool is_occupied(const std::pair<int, int>& p) const
    {
        return _map[std::get<0>(p)][std::get<1>(p)] == '#';
    }
    bool is_empty(const std::pair<int, int>& p) const
    {
        return _map[std::get<0>(p)][std::get<1>(p)] == 'L';
    }

    std::vector<std::pair<int, int>> get_neighbours(const std::pair<int, int>& p) const
    {
        const std::vector<std::pair<int, int>> dirs = {
            std::make_pair(-1, -1),
            std::make_pair(0, -1),
            std::make_pair(1, -1),
            
            std::make_pair(-1, 0),
            std::make_pair(1, 0),
            
            std::make_pair(-1, 1),
            std::make_pair(0, 1),
            std::make_pair(1, 1),
        };

        std::vector<std::pair<int, int>> result;
        for(const auto& dir : dirs)
        {
            const auto curr = get_dir(p, dir);
            if (is_valid(curr)) result.push_back(curr);
        }

        return result;
    }

    std::pair<int, int> get_dir(const std::pair<int, int>& start, const std::pair<int, int>& dir) const
    {
        return std::make_pair(start.first + dir.first, start.second + dir.second);
    }

    void run_once()
    {
    }

private:
    std::string filename;
    std::vector<std::vector<char>> _map;
};
