#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>

class Day16
{
public:
    Day16(std::string fname) : _filename(fname)
    {
        std::ifstream file(_filename);
        parse_stream(file);
        file.close();
        
        //std::stringstream ss("class: 0-1 or 4-19\nrow: 0-5 or 8-19\nseat: 0-13 or 16-19\n\nyour ticket:\n11,12,13\n\nnearby tickets:\n3,9,18\n15,1,5\n5,14,9\n");
        //parse_stream(ss);
    }

    void parse_stream(std::istream& stream)
    {
        std::string line;
        int step = 0;
        
        while(stream)
        {
            std::getline(stream, line);
            if (line.size() > 0)
            {
                switch (step)
                {
                    case 0:
                        parse_rule(line);
                        break;
                    case 1:
                        _ticket = parse_ticket(line);
                        break;
                    case 2:
                        if (line[0] != 'n') _near.push_back(parse_ticket(line));
                        break;
                }
            }
            else
            {
                step++;
            }
        }
    }

    void parse_rule(std::string rule)
    {
        std::stringstream ss(rule);

        std::string name;
        std::getline(ss, name, ':');
        ss.ignore(1);

        for(int i = 0; i < 2; ++i)
        {
            int min, max;
            
            ss >> min;
            ss.ignore(1);
            ss >> max;
            ss.ignore(4);

            _rules[name].push_back(std::make_pair(min, max));
        }
    }

    std::vector<int> parse_ticket(std::string line) const
    {
        std::vector<int> result;

        auto comma = line.find(',');
        while(comma != std::string::npos)
        {
            result.push_back(atoi(line.substr(0, comma).c_str()));
            line = line.substr(comma+1);
            comma = line.find(',');
        }
        result.push_back(atoi(line.c_str()));
        
        return result;
    }

    int64_t get_error_rate()
    {
        std::vector<int> invalid;
        for(auto it = _near.begin(); it != _near.end(); ++it)
        {
            std::for_each((*it).begin(), (*it).end(), [this, &invalid](const int& i)
            {
                for(const auto& r : _rules)
                {
                    if ((i >= r.second[0].first && i <= r.second[0].second) || (i >= r.second[1].first && i <= r.second[1].second))
                    {
                        return;
                    }
                }
                invalid.push_back(i);
            });
        }

        for(const int inv : invalid)
        {
            _near_valid = std::remove_if(_near.begin(), _near.end(), [inv](const std::vector<int>& ticket)
            {
                return std::find(ticket.begin(), ticket.end(), inv) < ticket.end();
            });
        }
        if (invalid.size() <= 0) _near_valid = _near.end();
        
        return std::accumulate(invalid.begin(), invalid.end(), 0);
    }

    int64_t get_part_2() const
    {
        std::map<std::string, std::set<int>> possible;
        for(const auto& r : _rules)
        {
            for(int j = 0; j < _near[0].size(); ++j)
            {
                possible[r.first].insert(j);
            }
            
            std::for_each(_near.begin(), _near_valid, [&possible, &r](const std::vector<int>& ticket)
            {
                for(int i = 0; i < ticket.size(); ++i)
                {
                    const bool match = (ticket[i] >= r.second[0].first && ticket[i] <= r.second[0].second) ||
                        (ticket[i] >= r.second[1].first && ticket[i] <= r.second[1].second);

                    if (!match && possible[r.first].find(i) != possible[r.first].end())
                    {
                        possible[r.first].erase(i);
                    }
                }
            });
        }

        const int max_iter = 100;
        int iter = 0;
        do
        {
            for(const auto& elem : possible)
            {
                if (elem.second.size() == 1)
                {
                    const int remove = *elem.second.begin();
                    
                    for(auto& inner : possible)
                    {
                        if (inner.second.size() > 1)
                        {
                            inner.second.erase(remove);
                        }
                    }
                }
                
            }

            iter++;
        }
        while(std::any_of(possible.begin(), possible.end(), [](const std::pair<std::string, std::set<int>>& p)
        {
            return p.second.size() > 1;
        }) || iter > max_iter);

        return std::accumulate(possible.begin(), possible.end(), 1LL, [this](const int64_t& total, const std::pair<std::string, std::set<int>>& p)
        {
            if (p.first.find("departure") != std::string::npos)
            {
                return total * _ticket[*p.second.begin()];
            }
            
            return total * 1;
        });
    }

private:
    std::string _filename;

    std::map<std::string, std::vector<std::pair<int, int>>> _rules;
    std::vector<int> _ticket;
    std::vector<std::vector<int>> _near;
    std::vector<std::vector<int>>::const_iterator _near_valid;
};
