#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

typedef std::tuple<std::string, std::string, std::string, std::string> bounds;

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
        
        const bounds first_bound = std::make_tuple(*(++raw.begin()), left, *(--raw.end()), right);
        return std::make_pair(tile_id, find_permutations(first_bound));
    }

    std::vector<bounds> find_permutations(const bounds& first) const
    {
        std::vector<bounds> result;
        result.push_back(first);

        // Rotations
        result.push_back(std::make_tuple(
            std::get<1>(first), std::get<2>(first), std::get<3>(first), std::get<0>(first)));
        result.push_back(std::make_tuple(
            std::get<2>(first), std::get<3>(first), std::get<0>(first), std::get<1>(first)));
        result.push_back(std::make_tuple(
            std::get<3>(first), std::get<0>(first), std::get<1>(first), std::get<2>(first)));

        // Flips
        std::vector<bounds> flips;
        std::for_each(result.begin(), result.end(), [&flips](const bounds& b)
        {
            std::string rev_top = std::get<0>(b);
            std::reverse(rev_top.begin(), rev_top.end());
            std::string rev_left = std::get<1>(b);
            std::reverse(rev_left.begin(), rev_left.end());
            std::string rev_bottom = std::get<2>(b);
            std::reverse(rev_bottom.begin(), rev_bottom.end());
            std::string rev_right = std::get<3>(b);
            std::reverse(rev_right.begin(), rev_right.end());
            
            flips.push_back(std::make_tuple(
                std::get<2>(b), rev_left, std::get<0>(b), rev_right));
            flips.push_back(std::make_tuple(
                rev_top, std::get<3>(b), rev_bottom, std::get<1>(b)));
            flips.push_back(std::make_tuple(
                rev_left, rev_top, rev_right, rev_bottom));
            flips.push_back(std::make_tuple(
                rev_right, rev_bottom, rev_left, rev_top));
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
        std::vector<std::vector<bounds>> result;
        const size_t count = static_cast<size_t>(sqrt(_combine.size()));
        
        for(size_t i = 0; i < count; i++)
        {
            std::vector<bounds> temp;
            for(size_t j = 0; j < count; j++)
            {
                temp.push_back(std::make_tuple("", "", "", ""));
            }
            result.push_back(temp);
        }

        std::vector<int> used_tiles;

        for(const auto& t : _combine)
        {
            used_tiles.push_back(t.first);

            for(const auto& b : t.second)
            {
                result[0][0] = b;
                
                const auto temp = find_arrangement_impl(result, used_tiles, 1, 0);
                if (used_tiles.size() == _combine.size())
                {
                    return temp;
                }
            }
            
            used_tiles.clear();
        }

        return result;
    }

    std::vector<std::vector<bounds>> find_arrangement_impl(std::vector<std::vector<bounds>>& partial, std::vector<int>& used_tiles, int x, int y) const
    {
        printf("[0][0] = %i [%lld]\n", used_tiles[0], used_tiles.size());
        return partial;
    }

private:
    std::string _filename;

    std::map<int, std::vector<bounds>> _combine;
    // All possible bounds for each tile, mapped to the tile id, front is OG tile setup
    // Each entry in combine bounds is in this order: top, left, bottom, right
};
