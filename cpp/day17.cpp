#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <set>
#include <vector>
#include <algorithm>
#include <limits>

typedef std::tuple<int64_t, int64_t, int64_t, int64_t> coord;

class Day17
{
public:
    Day17(std::string fname) : _filename(fname)
    {
        _limits.push_back(std::make_pair(
            std::numeric_limits<int64_t>::max(),
            std::numeric_limits<int64_t>::min()
        ));
        _limits.push_back(std::make_pair(
            std::numeric_limits<int64_t>::max(),
            std::numeric_limits<int64_t>::min()
        ));
        _limits.push_back(std::make_pair(
            0,
            0
        ));
        _limits.push_back(std::make_pair(
            0,
            0
        ));

        std::ifstream file(_filename);
        parse_stream(file);
        file.close();
        
        //std::stringstream ss(".#.\n..#\n###\n");
        //parse_stream(ss);
    }

    void activate(const int64_t x, const int64_t y, const int64_t z, const int64_t w)
    {
        if (x < _limits[0].first) _limits[0].first = x;
        if (x > _limits[0].second) _limits[0].second = x;
        
        if (y < _limits[1].first) _limits[1].first = y;
        if (y > _limits[1].second) _limits[1].second = y;
        
        if (z < _limits[2].first) _limits[2].first = z;
        if (z > _limits[2].second) _limits[2].second = z;
        
        if (w < _limits[3].first) _limits[3].first = w;
        if (w > _limits[3].second) _limits[3].second = w;

        _active.insert(std::make_tuple(x, y, z, w));
    }

    void deactivate(const int64_t x, const int64_t y, const int64_t z, const int64_t w)
    {
        _active.erase(std::make_tuple(x, y, z, w));
        
        _limits.clear();
        for(const auto& a : _active)
        {
            _limits.push_back(std::make_pair(
                std::numeric_limits<int64_t>::max(),
                std::numeric_limits<int64_t>::min()
            ));
            _limits.push_back(std::make_pair(
                std::numeric_limits<int64_t>::max(),
                std::numeric_limits<int64_t>::min()
            ));
            _limits.push_back(std::make_pair(
                std::numeric_limits<int64_t>::max(),
                std::numeric_limits<int64_t>::min()
            ));
            _limits.push_back(std::make_pair(
                std::numeric_limits<int64_t>::max(),
                std::numeric_limits<int64_t>::min()
            ));
            
            if (std::get<0>(a) < _limits[0].first) _limits[0].first = std::get<0>(a);
            if (std::get<0>(a) > _limits[0].second) _limits[0].second = std::get<0>(a);
            
            if (std::get<1>(a) < _limits[1].first) _limits[1].first = std::get<1>(a);
            if (std::get<1>(a) > _limits[1].second) _limits[1].second = std::get<1>(a);
            
            if (std::get<2>(a) < _limits[2].first) _limits[2].first = std::get<2>(a);
            if (std::get<2>(a) > _limits[2].second) _limits[2].second = std::get<2>(a);
            
            if (std::get<3>(a) < _limits[3].first) _limits[3].first = std::get<3>(a);
            if (std::get<3>(a) > _limits[3].second) _limits[3].second = std::get<3>(a);
        }
    }

    void parse_stream(std::istream& stream)
    {
        std::string line;

        const int64_t w = 0;
        const int64_t z = 0;
        int64_t y = 0;
        
        while(stream)
        {
            int64_t x = 0;
            
            std::getline(stream, line);
            for(const auto& c : line)
            {
                if (c == '#')
                {
                    activate(x, y, z, w);
                }
                ++x;
            }
            ++y;
        }
    }

    void debug_print() const
    {
        printf("========\n");
        for(auto w = _limits[3].first; w <= _limits[3].second; ++w)
        {
            for(auto z = _limits[2].first; z <= _limits[2].second; ++z)
            {
                printf("z=%lld, w=%lld\n", z, w);
                for(auto y = _limits[1].first; y <= _limits[1].second; ++y)
                {
                    for(auto x = _limits[0].first; x <= _limits[0].second; ++x)
                    {
                        printf("%c ", _active.find(std::make_tuple(x, y, z, w)) != _active.end() ? '#' : '.');
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        printf("========\n");
    }

    void simulate(int count)
    {
        for(int i = 0; i < count; ++i)
        {
            simulate_impl();
        }
    }

    void simulate_impl()
    {
        std::vector<coord> to_flip;

        for(auto w = _limits[3].first-1; w <= _limits[3].second+1; ++w)
        {
            for(auto z = _limits[2].first-1; z <= _limits[2].second+1; ++z)
            {
                for(auto y = _limits[1].first-1; y <= _limits[1].second+1; ++y)
                {
                    for(auto x = _limits[0].first-1; x <= _limits[0].second+1; ++x)
                    {
                        const auto cur = std::make_tuple(x, y, z, w);
                        const int64_t count = count_active_neighbour(cur);

                        if (_active.find(cur) != _active.end())
                        {
                            if (count != 2 && count != 3) to_flip.push_back(cur);
                        }
                        else
                        {
                            if (count == 3) to_flip.push_back(cur);
                        }
                    }
                }
            }
        }

        for(const auto& c : to_flip)
        {
            if (_active.find(c) != _active.end()) deactivate(std::get<0>(c), std::get<1>(c), std::get<2>(c), std::get<3>(c));
            else activate(std::get<0>(c), std::get<1>(c), std::get<2>(c), std::get<3>(c));
        }
    }

    std::vector<coord> get_neighbours(const coord& c) const
    {
        const std::vector<int> diffs = { -1, 0, 1 };
        std::vector<coord> result;

        for(const auto& w_diff : diffs)
        {
            for(const auto& z_diff : diffs)
            {
                for(const auto& y_diff : diffs)
                {
                    for(const auto& x_diff : diffs)
                    {
                        const auto& tup = std::make_tuple(
                            std::get<0>(c) + x_diff,
                            std::get<1>(c) + y_diff,
                            std::get<2>(c) + z_diff,
                            std::get<3>(c) + w_diff
                        );
                    
                        if (tup != c) result.push_back(tup);
                    }
                }
            }
        }
        
        return result;
    }

    int64_t count_active_neighbour(const coord& c)
    {
        const auto& neighbours = get_neighbours(c);
        return std::count_if(neighbours.begin(), neighbours.end(), [this](const coord& elem)
        {
            return _active.find(elem) != _active.end();
        });
    }

    int64_t active_count() const
    {
        return _active.size();
    }

private:
    std::string _filename;

    std::set<coord> _active;
    std::vector<std::pair<int64_t, int64_t>> _limits;
};
