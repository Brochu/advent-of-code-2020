#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

class Day19
{
public:
    Day19(std::string fname) : _filename(fname)
    {
        std::ifstream file(_filename);
        parse_stream(file);
        file.close();
        
        //std::stringstream ss("0: 4 1 5\n1: 2 3 | 3 2\n2: 4 4 | 5 5\n3: 4 5 | 5 4\n4: \"a\"\n5: \"b\"\n\nababbb\nbababa\nabbbab\naaabbb\naaaabbb\n");
        //parse_stream(ss);
    }

    void parse_stream(std::istream& stream)
    {
        std::string line;
        while(std::getline(stream, line))
        {
            if (line.size() <= 0) continue;
            
            if (line.find(":") != std::string::npos)
            {
                parse_rule(line);
            }
            else
            {
                _matches += check_message(line) ? 1 : 0;
            }
        }
    }

    void parse_rule(const std::string& line)
    {
        std::stringstream ss(line);
        int key;
        ss >> key;
        ss.ignore(2);
        
        if (line.find("\"") != std::string::npos)
        {
            ss.ignore(1);
            char c;
            ss >> c;
            
            _abs_rules[key] = c;
        }
        else
        {
            std::vector<std::vector<int>> full;
            
            std::string definition;
            while(std::getline(ss, definition, '|'))
            {
                full.push_back({});
                
                ss.ignore(1);
                std::stringstream def_stream(definition);
                int val;
                while(def_stream >> val)
                {
                    full[full.size()-1].push_back(val);
                }
            }
            
            _rel_rules[key] = full;
        }
    }

    bool check_message(const std::string& m, int rule = 0) const
    {
        std::string::const_iterator it = m.cbegin();
        
        const bool rules_match = check_message_impl(m, it, rule);
        printf("[FINAL][%s][done? %s]\n", rules_match ? "O" : "X", it==m.cend() ? "yes" : "no");
        printf("\n");
        return rules_match && it == m.cend();
    }

    bool check_message_impl(const std::string& m, std::string::const_iterator& it, int rule) const
    {
        if (it == m.cend()) return false;

        bool final_result;
        if (_abs_rules.find(rule) != _abs_rules.end())
        {
            final_result = _abs_rules.at(rule) == *(it);
            ++it;
        }
        else
        {
            // relative rule...
            std::string::const_iterator s_it(it);
            final_result = std::any_of(_rel_rules.at(rule).begin(), _rel_rules.at(rule).end(), [&](const std::vector<int> def)
            {
                bool result = true;
                for(const auto& e : def)
                {
                    result &= check_message_impl(m, it, e);
                    
                    if (!result)
                    {
                        it = s_it;
                        break;
                    }
                }

                return result;
            });
        }

        std::string debug;
        printf("[RULE %i][%s] %s from %lld\n", rule, final_result ? "O" : "X", m.c_str(), (it - m.cbegin()));
        return final_result;
    }

    int get_par1() const
    {
        return _matches;
    }

private:
    std::string _filename;

    std::map<int, std::vector<std::vector<int>>> _rel_rules;
    std::map<int, char> _abs_rules;

    int _matches;
};
