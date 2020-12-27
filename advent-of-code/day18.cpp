#include <string>
#include <istream>
#include <fstream>
#include <iosfwd>
#include <random>
#include <sstream>
#include <vector>

class Day18
{
public:
    Day18(std::string fname) : _filename(fname)
    {
        std::ifstream file(_filename);
        parse_stream(file);
        file.close();
        
        //std::stringstream ss("1 + 2 * 3 + 4 * 5 + 6\n");
        //parse_stream(ss);
    }

    void parse_stream(std::istream& stream)
    {
        std::string line;
        while(stream)
        {
            std::getline(stream, line);
            if (line.size() > 0)
            {
                std::reverse(line.begin(), line.end());
                _result.push_back(eval(line));
            }
        }
    }

    int64_t eval(const std::string& equation) const
    {
        int64_t lhs;
        char op;
        std::string rest;

        split_equation(equation, lhs, op, rest);


        if (rest.size() > 0)
        {
            printf("%lld %c %s\n", lhs, op, rest.c_str());
            if (op == '+') return lhs + eval(rest);
            if (op == '*') return lhs * eval(rest);
        }
        
        printf("%lld\n", lhs);
        return lhs;
    }

    void split_equation(const std::string& equation, int64_t& lhs, char& op, std::string& rest) const
    {
        std::stringstream ss(equation);

        if (equation[0] == ')')
        {
            int stack = 0;
            size_t offset;
            for(offset = 1; offset < equation.size(); ++offset)
            {
                if (stack == 0 && equation[offset] == '(') break;
                if (equation[offset] == '(') stack--;
                if (equation[offset] == ')') stack++;
            }
            const std::string sub = equation.substr(1, offset-1);

            lhs = eval(sub);
            if (equation.size() > offset+2)
            {
                ss = std::stringstream(equation.substr(offset+2));
            }
        }
        else
        {
            ss >> lhs;
            ss.ignore(1);
        }
        
        ss >> op;
        ss.ignore(1);

        std::getline(ss, rest);
    }

    std::vector<int64_t> get_results() const
    {
        return _result;
    }

private:
    std::string _filename;

    std::vector<int64_t> _result;
};
