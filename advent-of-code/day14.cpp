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
        printf("set memory at %i\b", addr);
        
        printf("Value before mask : %lld\n", val);
        const long long masked = masked_val(val);
        printf("Value after mask : %lld\n", masked);
        
        _mem[addr] = masked;
    }

    long long masked_val(long long val) const
    {
        long long masked = 0;
        for(auto it = _mask.begin(); it != _mask.end(); ++it)
        {
            const size_t i = it - _mask.begin();
            const long long temp = val >> ((_mask.size()-1)-i);
            const short bit = ((temp % 2) == 0) ? 0 : 1;
            if (*it == '1')
            {
                masked++;
            }
            else if (*it == 'X')
            {
                masked += bit;
            }

            if (it != _mask.end()-1)
            {
                masked = masked << 1;
            }
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
