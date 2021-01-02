#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

typedef std::tuple<int, int, int, int> tilesides;

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
                _tiles.insert(parse_tile(raw));
                raw.clear();
            }
            else
            {
                raw.push_back(line);
            }
        }

        _tiles.insert(parse_tile(raw));
    }

    std::pair<int, tilesides> parse_tile(const std::vector<std::string>& raw)
    {
        const std::string& first = *raw.begin();
        const size_t space = (first).find(' ');
        int id = atoi(first.substr(space+1).c_str());

        // Get sides
        std::string left_side;
        std::string right_side;
        std::for_each(++raw.cbegin(), raw.cend(), [&left_side, &right_side](const std::string& s)
        {
            left_side += *s.begin();
            right_side += *(--s.end());
        });
        
        return std::make_pair(id, std::make_tuple(
            get_hashed_side(*(++raw.begin())),
            get_hashed_side(left_side),
            get_hashed_side(right_side),
            get_hashed_side(*(--raw.end()))
        ));
    }

    int get_hashed_side(const std::string& data)
    {
        int hash = 0;
        for(auto it = data.begin(); it != data.end(); ++it)
        {
            hash = hash << 1;
            hash += (*it == '#') ? 1 : 0;
        }

        _hashes[hash]++;
        return hash;
    }

    void print_tiles() const
    {
        for(const auto& tile : _tiles)
        {
            printf("%i ====\n", tile.first);
            
            printf("\t top -> %i [%i]\n", std::get<0>(tile.second), _hashes.at(std::get<0>(tile.second)));
            printf("\t left -> %i [%i]\n", std::get<1>(tile.second), _hashes.at(std::get<1>(tile.second)));
            printf("\t right -> %i [%i]\n", std::get<2>(tile.second), _hashes.at(std::get<2>(tile.second)));
            printf("\t bottom -> %i [%i]\n", std::get<3>(tile.second), _hashes.at(std::get<3>(tile.second)));
            printf("\n");
        }
    }

private:
    std::string _filename;

    std::map<int, tilesides> _tiles; // ID => [hashes] top, left, bottom,  right
    // hash = binary representation of the sides, compare between them to find matches
    // hash idea doesn't work, look into something else, so we can handle rotations better...
    std::map<int, int> _hashes;
};
