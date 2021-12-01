#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>

class Day14
{
public:
    Day14(char* fname, bool day2 = false) : _filename(fname), _day2(day2)
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
            parse_instr(line);
        }
        file.close();
    }
    
    void parse_debug()
    {
        std::string debug = "mask = 000000000000000000000000000000X1001X\nmem[42] = 100\nmask = 00000000000000000000000000000000X0XX\nmem[26] = 1\n";
        
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
            long long addr;
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

    void set_mem(long long addr, long long val)
    {
        if (!_day2)
        {
            printf("set memory at %lld\n", addr);
            
            printf("Value before mask : %lld\n", val);
            const long long masked = masked_val(val);
            printf("Value after mask : %lld\n", masked);
            
            _mem[addr] = masked;
        }
        else
        {
            for(const auto& a : masked_addrs(addr))
            {
                printf("Setting mem at %lld to %lld\n", a, val);
                _mem[a] = val;
            }
        }
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

    std::vector<long long> masked_addrs(const long long addr)
    {
        std::vector<long long> addrs;
        addrs.push_back(0);
        
        for(auto it = _mask.begin(); it != _mask.end(); ++it)
        {
            const size_t i = it - _mask.begin();
            const long long temp = addr >> ((_mask.size()-1)-i);
            const short bit = ((temp % 2) == 0) ? 0 : 1;
            if (*it == '1')
            {
                for(auto ait = addrs.begin(); ait != addrs.end(); ++ait)
                {
                    (*ait)++;
                }
            }
            else if (*it == '0')
            {
                for(auto ait = addrs.begin(); ait != addrs.end(); ++ait)
                {
                    (*ait) += bit;
                }
            }
            else if (*it == 'X')
            {
                for(long long j = addrs.size()-1; j >=0 ; --j)
                {
                    long long t = addrs[j];
                    addrs.push_back(++t);
                }
            }

            if (it != _mask.end()-1)
            {
                for(auto ait = addrs.rbegin(); ait != addrs.rend(); ++ait)
                {
                    (*ait) = (*ait) << 1;
                }
            }
        }

        return addrs;
    }

    long long mem_sum() const
    {
        return std::accumulate(_mem.begin(), _mem.end(), 0LL,
            [](const long long val, const std::pair<long long, long long>& p)
            { return val + p.second; });
    }

private:
    std::string _filename;

    std::string _mask;
    std::map<long long, long long> _mem;

    bool _day2;
};
