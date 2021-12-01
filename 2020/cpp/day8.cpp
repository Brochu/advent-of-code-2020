#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

class Day8
{
public:
    Day8(char* fname) : filename(fname)
    { }

    void parse_file()
    {
        std::ifstream file(filename);
        std::string line;

        while(file)
        {
            std::getline(file, line);
            _instr.push_back(line);
        }
        file.close();
    }

    void parse_debug(std::string assembly)
    {
        std::stringstream ss(assembly);
        std::string line;

        while(!ss.eof())
        {
            std::getline(ss, line);
            _instr.push_back(line);
        }
    }

    void force_complete_run()
    {
        for(int i = 0; i < _instr.size(); ++i)
        {
            if (_instr[i].find("nop") != std::string::npos)
            {
                auto tmp_rules(_instr);
                tmp_rules[i].replace(0, 3, "jmp");
                if (run_instrs(tmp_rules)) return;
            }
            if (_instr[i].find("jmp") != std::string::npos)
            {
                auto tmp_rules(_instr);
                tmp_rules[i].replace(0, 3, "nop");
                if (run_instrs(tmp_rules)) return;
            }
        }
    }

    bool run_program()
    {
        bool keep_running = true;
        while(keep_running && _pc < _instr.size())
        {
            keep_running = parse_opcode(_instr[_pc]);
        }

        return keep_running;
    }

    bool run_instrs(std::vector<std::string> instr)
    {
        _pc = 0;
        _acc = 0;
        _ran_instr.clear();
        
        bool keep_running = true;
        while(keep_running && _pc < instr.size())
        {
            keep_running = parse_opcode(instr[_pc]);
        }

        return keep_running;
    }

    bool parse_opcode(std::string opcode)
    {
        if (_ran_instr.find(_pc) == _ran_instr.end())
        {
            _ran_instr.insert(_pc);
        }
        else
        {
            // Detected infinite loop
            return false;
        }
        
        std::stringstream ss(opcode);
        std::string code;
        int arg;

        ss >> code;
        ss >> arg;

        if (code == "acc")
        {
            acc_call(arg);
        }
        else if (code == "jmp")
        {
            jmp_call(arg);
        }
        else
        {
            // NOP
            ++_pc;
            printf("[NOP] arg: %i, new pc: %i\n", arg, _pc);
        }
        return true;
    }

    void acc_call(int arg)
    {
        _acc += arg;
        ++_pc;

        printf("[ACC] arg: %i, new acc: %i | new pc: %i\n", arg, _acc, _pc);
    }

    void jmp_call(int arg)
    {
        _pc += arg;
        printf("[JMP] arg: %i, new pc: %i\n", arg, _pc);
    }

    int get_acc() const
    {
        return _acc;
    }

private:
    std::string filename;
    std::vector<std::string> _instr;
    std::set<int> _ran_instr;

    int _pc;
    int _acc;
};
