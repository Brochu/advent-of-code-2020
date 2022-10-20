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
        init_from_file();
        //init_from_debug();
    }

    void init_from_file()
    {
        std::ifstream file(filename);
        std::string line;
        while(file)
        {
            std::getline(file, line);
            if (line.size() == 0) break;
            
            _map.emplace_back();
            
            std::vector<char>& current_list = _map[_map.size()-1];
            for(const char& c : line)
            {
                current_list.push_back(c);
            }
        }
    }
    
    void init_from_debug()
    {
        std::string input = "L.LL.LL.LL\nLLLLLLL.LL\nL.L.L..L..\nLLLL.LL.LL\nL.LL.LL.LL\nL.LLLLL.LL\n..L.L.....\nLLLLLLLLLL\nL.LLLLLL.L\nL.LLLLL.LL\n";
        
        std::stringstream ss(input);
        std::string line;
        while(ss)
        {
            std::getline(ss, line);
            if (line.size() == 0) break;
            
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
        printf("==================\n");
        for(int i = 0; i < _map.size(); ++i)
        {
            for(int j = 0; j < _map[i].size(); ++j)
            {
                printf("%c", _map[i][j]);
            }
            printf("\n");
        }
        
        printf("==================\n");
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
    bool is_nothing(const std::pair<int, int>& p) const
    {
        return _map[std::get<0>(p)][std::get<1>(p)] == '.';
    }

    void flip_state(const std::pair<int, int>& p)
    {
        const char& current = _map[p.first][p.second];
        if (current == '#')
        {
            _map[p.first][p.second] = 'L';
        }
        else if (current == 'L')
        {
            _map[p.first][p.second] = '#';
        }
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
            const auto curr = std::make_pair(p.first + dir.first, p.second + dir.second);
            if (is_valid(curr)) result.push_back(curr);
        }

        return result;
    }

    std::vector<std::pair<int, int>> get_neighbours_view(const std::pair<int, int>& p) const
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
            
            auto curr = std::make_pair(p.first + dir.first, p.second + dir.second);
            while(is_valid(curr) && is_nothing(curr))
            {
                curr = std::make_pair(curr.first + dir.first, curr.second + dir.second);
            }
            
            if (is_valid(curr) && !is_nothing(curr)) result.push_back(curr);
        }
        
        return result;
    }

    int count_occupied_adj(const std::pair<int, int>& p, bool day1 = true) const
    {
        const auto& ajds = day1 ? get_neighbours(p) : get_neighbours_view(p);
        const auto op = [this](int total, const std::pair<int, int>& item)
        {
            total += is_occupied(item) ? 1 : 0;
            return total;
        };

        return std::accumulate(ajds.cbegin(), ajds.cend(), 0, op);
    }

    long long count_occupied() const
    {
        std::vector<long long> partial;
        std::transform(_map.begin(), _map.end(), std::back_inserter(partial),
        [](const std::vector<char>& row)
        {
            return std::count_if(row.begin(), row.end(), [](const char& c){ return c == '#'; });
        });
        
        return std::accumulate(partial.begin(), partial.end(), 0LL);
    }

    bool run_once(bool day1 = true)
    {
        std::vector<std::pair<int, int>> to_flip;
        
        for(int i = 0; i < _map.size(); ++i)
        {
            for(int j = 0; j < _map[i].size(); ++j)
            {
                const auto& current = std::make_pair(i, j);
                const int occupied_ajds = count_occupied_adj(current, day1);

                if ((_map[current.first][current.second] == 'L' && occupied_ajds == 0) ||
                    (_map[current.first][current.second] == '#' && occupied_ajds >= (day1 ? 4 : 5)))
                {
                    to_flip.push_back(current);
                }
            }
        }

        std::for_each(to_flip.begin(), to_flip.end(), [this](const auto& p){ flip_state(p); });

        return to_flip.size() > 0;
    }

private:
    std::string filename;
    std::vector<std::vector<char>> _map;
};
