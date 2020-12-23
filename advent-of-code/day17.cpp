#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <map>

class Day17
{
public:
    Day17(std::string fname) : _filename(fname)
    {
        //std::ifstream file(_filename);
        //parse_stream(file);
        //file.close();
        
        std::stringstream ss(".#.\n..#\n###\n");
        parse_stream(ss);
    }

    void parse_stream(std::istream& stream)
    {
        std::string line;
        
        const int64_t z = 0;
        int64_t y = 0;
        
        while(stream)
        {
            int64_t x = 0;
            
            std::getline(stream, line);
            for(const auto& c : line)
            {
                printf("%c ", c);
                _map[z][y][x] = c == '#';
                ++x;
            }
            printf("\n");
            ++y;
        }
    }

    void debug_print() const
    {
        printf("========");
        for(const auto& z : _map)
        {
            printf("Z=%lld\n", z.first);
            for(const auto& y : z.second)
            {
                for(const auto& x : y.second)
                {
                    printf("%c ", x.second ? '#' : '.');
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("========");
    }

private:
    std::string _filename;

    std::map<int64_t, std::map<int64_t, std::map<int64_t, bool>>> _map; // _map[z][x][y] = active or not
};
