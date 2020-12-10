#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include <algorithm>

class Day7
{
public:
    Day7(char* fname) : filename(fname)
    {
        this->init_rules();
    }

    void init_rules()
    {
        std::ifstream file(filename);
        std::string line;

        std::string container;
        std::string contains;
        while(file)
        {
            std::getline(file, line);

            const size_t contain_idx = line.find("contain ");
            if (contain_idx < line.size())
            {
                container = line.substr(0, contain_idx-2);
                contains = line.substr(contain_idx+7);
                
                size_t next_comma = contains.find(", ");
                int count;
                std::string bag;
                while(next_comma < contains.size())
                {
                    count = atoi(contains.substr(1, 1).c_str());
                    bag = contains.substr(3, next_comma-3);

                    if (count > 0)
                    {
                        if (bag[bag.size()-1] == 's') bag = bag.substr(0, bag.size()-1);
                        _rules[container].push_back(std::make_pair(count, bag));
                    }

                    contains = contains.substr(next_comma + 1);
                    next_comma = contains.find(", ");
                }
                count = atoi(contains.substr(1, 1).c_str());
                bag = contains.substr(3, contains.size()-4);

                if (count > 0)
                {
                    if (bag[bag.size()-1] == 's') bag = bag.substr(0, bag.size()-1);
                    _rules[container].push_back(std::make_pair(count, bag));
                }
                else
                {
                    _rules[container].reserve(0);
                }
            }
        }
        
        file.close();
    }

    std::set<std::string> get_all_outermost(std::string bag_name) const
    {
        std::set<std::string> all_bags;
        get_all_outermost_impl(bag_name, all_bags);
        
        return all_bags;
    }

    void get_all_outermost_impl(std::string bag_name, std::set<std::string>& bags) const
    {
        std::set<std::string> new_bags;
        for(const auto& r : _rules)
        {
            const auto& contains = std::get<1>(r);
            const auto pred = [&bag_name](const auto& p){ return std::get<1>(p) == bag_name; };
            
            if (bags.find(std::get<0>(r)) == bags.end() && std::any_of(contains.cbegin(), contains.cend(), pred))
            {
                new_bags.insert(std::get<0>(r));
                bags.insert(std::get<0>(r));
            }
        }

        if (new_bags.size() > 0)
        {
            for(const auto& b : new_bags)
            {
                get_all_outermost_impl(b, bags);
            }
        }
    }

    int get_max_count(std::string bag_name)
    {
        int count;
        auto& rule = _rules[bag_name];
        if (rule.size() > 0)
        {
            count = std::accumulate(rule.begin(), rule.end(), 0,
                [this](int t, const std::pair<int, std::string>& e)
                {
                    int total = get_max_count(std::get<1>(e));
                    printf("[%s] %i * %i\n", std::get<1>(e).c_str(), std::get<0>(e), total);
                    return t + std::get<0>(e) * total;
                });
        }
        else
        {
            count = 1;
        }

        return count;
    }

private:
    std::string filename;
    std::map<std::string, std::vector<std::pair<int, std::string>>> _rules;
};
