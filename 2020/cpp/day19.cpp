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
        //std::ifstream file(_filename);
        //parse_stream(file);
        //file.close();

        std::stringstream ss("42: 9 14 | 10 1\n9: 14 27 | 1 26\n10: 23 14 | 28 1\n1: \"a\"\n11: 42 31\n5: 1 14 | 15 1\n19: 14 1 | 14 14\n12: 24 14 | 19 1\n16: 15 1 | 14 14\n31: 14 17 | 1 13\n6: 14 14 | 1 14\n2: 1 24 | 14 4\n0: 8 11\n13: 14 3 | 1 12\n15: 1 | 14\n17: 14 2 | 1 7\n23: 25 1 | 22 14\n28: 16 1\n4: 1 1\n20: 14 14 | 1 15\n3: 5 14 | 16 1\n27: 1 6 | 14 18\n14: \"b\"\n21: 14 1 | 1 14\n25: 1 1 | 1 14\n22: 14 14\n8: 42\n26: 14 22 | 1 20\n18: 15 15\n7: 14 5 | 1 21\n24: 14 \n1\nabbbbbabbbaaaababbaabbbbabababbbabbbbbbabaaaa\nbbabbbbaabaabba\nbabbbbaabbbbbabbbbbbaabaaabaaa\naaabbbbbbaaaabaababaabababbabaaabbababababaaa\nbbbbbbbaaaabbbbaaabbabaaa\nbbbababbbbaaaaaaaabbababaaababaabab\nababaaaaaabaaab\nababaaaaabbbaba\nbaabbaaaabbaaaababbaababb\nabbbbabbbbaaaababbbbbbaaaababb\naaaaabbaabaaaaababaa\naaaabbaaaabbaaa\naaaabbaabbaaaaaaabbbabbbaaabbaabaaa\nbabaaabbbaaabaababbaabababaaab\naabbbbbaabbbaaaaaabbbbbababaaaaabbaaabba\n");
        parse_stream(ss);
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
