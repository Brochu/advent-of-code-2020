#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>

typedef std::vector<std::string> Tile;
typedef std::vector<std::pair<int, std::vector<std::string>>>::iterator Tile_Ptr;

enum Sides
{
    TOP = 0,
    LEFT,
    BOTTOM,
    RIGHT
};

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
            raw.push_back(line);
        }

        // Split tiles
        auto start = raw.cbegin();
        auto end = raw.cbegin();

        while(start != raw.cend())
        {
            end = std::find(start, raw.cend(), "");
            
            const int tile_id = atoi((*start).substr((*start).find(' ')).c_str());
            const Tile t(start+1, end);
            _tiles[tile_id] = t;
            enum_rotations(tile_id, t);

            start = (end != raw.cend()) ? end+1 : end;
        }
    }

    void enum_rotations(int id, const Tile& t)
    {
        _all.push_back(std::make_pair(id, t));
        _all.push_back(std::make_pair(id, rotate(_all.back().second)));
        _all.push_back(std::make_pair(id, rotate(_all.back().second)));
        _all.push_back(std::make_pair(id, rotate(_all.back().second)));

        _all.push_back(std::make_pair(id, reflectX(t)));
        _all.push_back(std::make_pair(id, reflectY(t)));
        _all.push_back(std::make_pair(id, transpose(t)));
        _all.push_back(std::make_pair(id, reflectDiag(t)));
    }

    Tile rotate (Tile t)
    {
        const auto& cycle = [](char& a, char& b, char& c, char& d)
        {
           const int temp = a;
           a = b;
           b = c;
           c = d;
           d = temp;
        };
        
        for(int i=0; i < _n/2; i++)
            for(int j=0; j < (_n+1)/2; j++)
                cycle(t[i][j], t[_n-1-j][i], t[_n-1-i][_n-1-j], t[j][_n-1-i]);

        return t;
    }

    Tile reflectX(Tile t)
    {
        for(size_t i = 0; i < _n; ++i)
        {
            for(size_t j = 0; j < _n/2; ++j)
            {
                const char temp = t[i][j];
                t[i][j] = t[i][_n-j-1];
                t[i][_n-j-1] = temp;
            }
        }
        return t;
    }
    
    Tile reflectY(Tile t)
    {
        for(size_t i = 0; i < _n/2; ++i)
        {
            for(size_t j = 0; j < _n; ++j)
            {
                const char temp = t[i][j];
                t[i][j] = t[_n-i-1][j];
                t[_n-i-1][j] = temp;
            }
        }
        return t;
    }

    Tile transpose(Tile t)
    {
        Tile result(t);
        
        for(size_t i = 0; i < _n; ++i)
            for(size_t j = 0; j < _n; ++j)
                result[i][j] = t[j][i];
        
        return result;
    }
    
    Tile reflectDiag(Tile t)
    {
        for (int i = 0; i < (_n - 1); i++)
        {
            for (int j = 0; j < (_n - 1) - i; j++)
            {
                int tmp = t[i][j];
                t[i][j] = t[(_n - 1) - j][(_n - 1) - i];
                t[(_n - 1) - j][(_n - 1) - i] = tmp;
            }
        }
        return t;
    }

    std::string get_side(const Tile& t, Sides s) const
    {
        std::string line;
        
        switch(s)
        {
            case TOP:
                line = *t.begin();
                break;
            
            case LEFT:
                std::transform(t.begin(), t.end(), std::back_inserter(line), [](const std::string& s)
                { return *s.begin(); });
                break;
            
            case BOTTOM:
                line = *(t.end()-1);
                break;
            
            case RIGHT:
                std::transform(t.begin(), t.end(), std::back_inserter(line), [](const std::string& s)
                { return *(s.end()-1); });
                break;
                
            default: return "INVALID";
        }
        return line;
    }

    std::vector<int> solve() const
    {
        const int side = static_cast<int>(sqrt(_tiles.size()));
        
        std::vector<size_t> result;
        int idx = 0;
        
        std::set<int> available;
        std::transform(_tiles.cbegin(), _tiles.cend(), std::inserter(available, available.end()),
            [](const std::pair<int, Tile>& t) { return t.first; });
        
        for(size_t i = 0; i < _all.size(); ++i)
        {
            result.push_back(i);
            available.erase(_all.at(i).first);

            if (solve_impl(result, available, idx+1, side))
            {
                std::vector<int> ret;
                std::transform(result.cbegin(), result.cend(), std::back_inserter(ret),
                    [this](const size_t& val){ return _all.at(val).first; });
                return ret;
            }
            
            available.insert(_all.at(i).first);
            result.pop_back();
        }

        return {};
    }

    bool solve_impl(std::vector<size_t>& partial, std::set<int> available, int index, int side) const
    {
        for(int i = 0; i < _all.size(); ++i)
        {
            // Cannot use the same tile twice
            if(available.find(_all.at(i).first) == available.end()) continue;
            
            if (index%side != 0)
            {
                // Compare t's left with index-1's right
                const std::string& t_left = get_side(_all.at(i).second, Sides::LEFT);
                const std::string& prev_right = get_side(_all.at(partial[index-1]).second, Sides::RIGHT);

                if (t_left != prev_right) continue;
            }
            
            if (index >= side)
            {
                // Compare t's top with index-side's bottom
                const std::string& t_top = get_side(_all.at(i).second, Sides::TOP);
                const std::string& prev_bottom = get_side(_all.at(partial[index-side]).second, Sides::BOTTOM);

                if (t_top != prev_bottom) continue;
            }

            partial.push_back(i);
            available.erase(_all.at(i).first);

            if (available.size() == 0) return true;

            if (solve_impl(partial, available, index+1, side))
            {
                return true;
            }
            
            available.insert(_all.at(i).first);
            partial.pop_back();
        }
        return false;
    }

private:
    std::string _filename;

    const size_t _n = 10;
    std::map<int, Tile> _tiles;
    std::vector<std::pair<int, Tile>> _all;
};
