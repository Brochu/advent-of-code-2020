#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>

class Day14
{
public:
    Day14(char* fname) : _filename(fname)
    {
        //parse_file();
        parse_debug();
    }

    void parse_file()
    {
    }
    
    void parse_debug()
    {
        std::string debug = "mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X\nmem[8] = 11\nmem[7] = 101\nmem[8] = 0\n";
        
        std::stringstream ss(debug);
        std::string line;
        while(ss)
        {
            std::getline(ss, line);
            
            if (line.size() > 0)
            {
                parse_instr(line);
            }
        }
    }

    void parse_instr(std::string instr)
    {
        std::stringstream ss(instr);
        std::string opcode;

        std::getline(ss, opcode, '=');
        opcode = opcode.substr(0, opcode.size()-1);

        if (opcode == "mask")
        {
            std::string mask;
            std::getline(ss, mask);
            mask = mask.substr(1);

            set_mask(mask);
        }
        else if (opcode.substr(0, 3) == "mem")
        {
            std::stringstream op_ss(opcode.substr(4));
            int addr;
            long long val;

            op_ss >> addr;
            ss >> val;

            set_mem(addr, val);
        }
    }

    void set_mask(std::string new_mask)
    {
        printf("set mask to %s\n", new_mask.c_str());
        _mask = new_mask;
    }

    void set_mem(int addr, long long val)
    {
        printf("set memory at %i to %lld\n", addr, val);
        _mem[addr] = masked_val(val);
    }

    long long masked_val(long long val) const
    {
        int masked = 0;
        for(int i = 0; i < _mask.size(); ++i)
        {
        }
        return masked;
    }

    long long mem_sum() const
    {
        return std::accumulate(_mem.begin(), _mem.end(), 0LL,
            [](const long long val, const std::pair<int, long long>& p)
            { return val + p.second; });
    }

private:
    std::string _filename;

    std::string _mask;
    std::map<int, long long> _mem;
};
