#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>

class Day18
{
public:
    Day18(std::string fname) : _filename(fname)
    {
        std::ifstream file(_filename);
        //parse_stream(file);
        parse_part2(file);
        file.close();
        
        //std::stringstream ss("1 + (2 * 3) + (4 * (5 + 6))\n");
        //parse_stream(ss);
        //parse_part2(ss);
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

    void parse_part2(std::istream& stream)
    {
        std::string line;
        while(stream)
        {
            std::getline(stream, line);
            if (line.size() > 0)
            {
                _result.push_back(get(line));
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
            if (op == '+') return lhs + eval(rest);
            if (op == '*') return lhs * eval(rest);
        }
        return lhs;
    }

    int64_t get(std::string& equation) const
    {
        //printf("#%s#\n", equation.c_str());
        
        size_t paren = equation.find("(");
        while(paren != std::string::npos)
        {
            size_t length = 1;
            int stack = 1;
            for(size_t i = paren+1; i < equation.size(); ++i)
            {
                length++;
                
                if (equation[i] == '(') stack++;
                if (equation[i] == ')' && stack == 1) break;
                if (equation[i] == ')') stack--;
            }

            std::string sub_equation = equation.substr(paren+1, length-2);
            const auto result = get(sub_equation);
            equation.erase(paren, length);
            equation.insert(paren, std::to_string(result));

            
            paren = equation.find("(", paren+1);
        }
        
        //printf("#%s#\n", equation.c_str());
        
        std::stringstream ss(equation);
        std::string part;

        int64_t total = 1;
        while(std::getline(ss, part, '*'))
        {
            int64_t subtotal = 0;
            std::stringstream subss(part);
            std::string c;
            while(std::getline(subss, c, '+'))
            {
                subtotal += atoi(c.c_str());
            }
            total *= subtotal;
            
            ss.ignore(1);
        }

        return total;
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

    int64_t get_part1() const
    {
        return std::accumulate(_result.begin(), _result.end(), 0LL);
    }

private:
    std::string _filename;

    std::vector<int64_t> _result;
};
