#include <string>
#include <fstream>
#include <iosfwd>
#include <sstream>
#include <vector>

class Day12
{
public:
    Day12(char* fname) : _filename(fname)
    {
        parse_file();
        //parse_debug();
    }

    void parse_file()
    {
        std::ifstream file(_filename);
        std::string line;
        
        while(file)
        {
            std::getline(file, line);
            if (line.size() > 0)
            {
                exec(line);
            }
        }
    }
    
    void parse_debug()
    {
        std::stringstream ss("F10\nN3\nF7\nR90\nF11\n");
        std::string line;
        
        while(ss)
        {
            std::getline(ss, line);
            if (line.size() > 0)
            {
                exec(line);
            }
        }
    }

    void exec(std::string instr)
    {
        const char op = instr[0];
        const int arg = atoi(instr.substr(1).c_str());

        if (op == 'N') exec_north(arg);
        else if (op == 'S') exec_south(arg);
        else if (op == 'E') exec_east(arg);
        else if (op == 'W') exec_west(arg);
        else if (op == 'L') exec_left(arg);
        else if (op == 'R') exec_right(arg);
        else if (op == 'F') exec_forward(arg);
        
        printf("%s; boat(%i, %i); WP(%i, %i)\n", instr.c_str(), _east, _north, _wp_east, _wp_north);
    }

    void exec_north(const int arg) { _wp_north += arg; }
    void exec_south(const int arg) { _wp_north -= arg; }
    void exec_east(const int arg) { _wp_east += arg; }
    void exec_west(const int arg) { _wp_east -= arg; }
    void exec_left(const int arg)
    {
        for(int i = 0; i < arg / 90; ++i)
        {
            std::swap(_wp_north, _wp_east);
            _wp_east *= -1;
        }
        _facing = (_facing + arg) % 360;
    }
    void exec_right(const int arg)
    {
        for(int i = 0; i < arg / 90; ++i)
        {
            std::swap(_wp_north, _wp_east);
            _wp_north *= -1;
        }
        
        _facing -= arg;
        if (_facing < 0) _facing = 360 - abs(_facing);
    }
    void exec_forward(const int arg)
    {
        //exec(get_facing_dir() + std::to_string(arg));
        _north += (arg * _wp_north);
        _east += (arg * _wp_east);
    }

    std::string get_facing_dir() const
    {
        if (_facing == 0) return "E";
        if (_facing == 90) return "N";
        if (_facing == 180) return "W";
        if (_facing == 270) return "S";
        
        return "N/A";
    }

    int get_man_dist() const
    {
        return abs(_east) + abs(_north);
    }

private:
    std::string _filename;
    
    int _facing = 0;
    int _east = 0;
    int _north = 0;

    int _wp_east = 10;
    int _wp_north = 1;
};
