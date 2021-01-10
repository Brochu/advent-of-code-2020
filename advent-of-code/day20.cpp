#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>

typedef std::array<std::string, 4> bounds;

class Day20
{
public:
    Day20(std::string fname) : _filename(fname)
    {
        std::ifstream file(_filename);
        parse_stream(file);
        file.close();
    }

    void parse_stream(std::istream& stream)
    {
        std::string line;
        std::vector<std::string> raw;
        
        while(std::getline(stream, line))
        {
            if (line.size() <= 0)
            {
                _combine.insert(parse_tile(raw));
                raw.clear();
            }
            else
            {
                raw.push_back(line);
            }
        }

        _combine.insert(parse_tile(raw));
    }

    std::pair<int, std::vector<bounds>> parse_tile(const std::vector<std::string>& raw) const
    {
        const size_t space = raw.front().find(" ");
        const int tile_id = atoi(raw.front().substr(space+1).c_str());
        
        std::string left;
        std::string right;
        std::for_each(++raw.begin(), raw.end(), [&left, &right](const std::string& elem)
        {
            left += elem.front();
            right += elem.back();
        });
        
        const bounds first_bound = { *(++raw.begin()), left, *(--raw.end()), right };
        return std::make_pair(tile_id, find_permutations(first_bound));
    }

    std::vector<bounds> find_permutations(const bounds& first) const
    {
        std::vector<bounds> result;
        result.push_back(first);

        // Rotations
        result.push_back({ first[1], first[2], first[3], first[0] });
        result.push_back({ first[2], first[3], first[0], first[1] });
        result.push_back({ first[3], first[0], first[1], first[2] });

        // Flips
        std::vector<bounds> flips;
        std::for_each(result.begin(), result.end(), [&flips](const bounds& b)
        {
            std::string rev_top = b[0];
            std::reverse(rev_top.begin(), rev_top.end());
            std::string rev_left = b[1];
            std::reverse(rev_left.begin(), rev_left.end());
            std::string rev_bottom = b[2];
            std::reverse(rev_bottom.begin(), rev_bottom.end());
            std::string rev_right = b[3];
            std::reverse(rev_right.begin(), rev_right.end());
            
            flips.push_back({ b[2], rev_left, b[0], rev_right });
            flips.push_back({ rev_top, b[3], rev_bottom, b[1] });
            flips.push_back({ rev_left, rev_top, rev_right, rev_bottom });
            flips.push_back({ rev_right, rev_bottom, rev_left, rev_top });
        });

        result.reserve(result.size() + flips.size());
        result.insert(result.end(), flips.begin(), flips.end());
        
        return result;
    }

    void print_tiles(int tile_id) const
    {
        const std::vector<bounds>& selected = _combine.at(tile_id);
        
        printf("ID: %i\n", tile_id);
        std::for_each(selected.begin(), selected.end(), [](const bounds& b)
        {
            printf("TOP => %s\n", std::get<0>(b).c_str());
            printf("LEFT => %s\n", std::get<1>(b).c_str());
            printf("BOTTOM =>%s\n", std::get<2>(b).c_str());
            printf("RIGHT =>%s\n", std::get<3>(b).c_str());
            printf("\n");
        });
    }

    std::vector<int> get_tile_ids() const
    {
        std::vector<int> result;
        std::transform(_combine.begin(), _combine.end(), std::back_inserter(result), [](const auto& a)
        {
            return a.first;
        });

        return result;
    }

    std::vector<std::vector<bounds>> find_arrangement() const
    {
        const size_t count = static_cast<size_t>(sqrt(_combine.size()));
        
        std::vector<std::vector<bounds>> result(count);
        for(auto& b : result)
        {
            b = std::vector<bounds>(count);
        }
        
        std::vector<int> used_tiles;

        for(const auto& t : _combine)
        {
            used_tiles.push_back(t.first);

            for(const auto& b : t.second)
            {
                result[0][0] = b;
                if (find_arrangement_impl(result, used_tiles))
                {
                    return result;
                }
            }
            
            used_tiles.clear();
        }

        return result;
    }

    bool find_arrangement_impl(std::vector<std::vector<bounds>>& partial, std::vector<int>& used_tiles, int x = 0, int y = 0) const
    {
        const auto to_check = check_coords(x, y, partial.size());
        const auto origin = std::make_pair(x, y);
        const bounds& current = partial[x][y];
        
        for(const auto& c : to_check)
        {
            const int int_idx = find_interface_index(origin, c);
            printf("(%i, %i) -> [%i][%i]: %s\n", c.first, c.second, int_idx, opposite_side(int_idx), current[int_idx].c_str());
        }
        
        return true;
    }

    std::vector<std::pair<int, int>> check_coords(int x, int y, size_t max) const
    {
        std::vector<std::pair<int, int>> result;
        
        for(const auto& x_diff : {-1, 1})
        {
            if (is_valid(x+x_diff, y, max)) result.push_back(std::make_pair(x+x_diff, y));
        }
        for(const auto& y_diff : {-1, 1})
        {
            if (is_valid(x, y+y_diff, max)) result.push_back(std::make_pair(x, y+y_diff));
        }

        return result;
    }

    bool is_valid(int x, int y, size_t max) const
    { return x >= 0 && x < max && y >= 0 && y < max; }

    int find_interface_index(const std::pair<int, int>& coords, const std::pair<int, int>& check) const
    {
        const int x_diff = check.first - coords.first;
        if (x_diff == -1) return 1;
        if (x_diff == 1) return 3;
        
        const int y_diff = check.second - coords.second;
        if (y_diff == -1) return 0;
        if (y_diff == 1) return 2;

        // Should not happen
        return -1;
    }

    int opposite_side(int idx) const
    { return (idx + 2) % 4; }

private:
    std::string _filename;

    std::map<int, std::vector<bounds>> _combine;
    // All possible bounds for each tile, mapped to the tile id, front is OG tile setup
    // Each entry in combine bounds is in this order: top, left, bottom, right
};
