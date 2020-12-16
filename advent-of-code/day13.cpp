#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Day13
{
public:
    Day13(char* fname) : _filename(fname)
    {
        //parse_file();
        parse_debug();
    }

    void parse_file()
    {
        std::ifstream file(_filename);
        std::string raw_early;
        std::string service;
        
        std::getline(file, raw_early);
        earliest = atoi(raw_early.c_str());

        std::getline(file, service, ',');
        while(file)
        {
            if (service[0] != 'x')
            {
                _buses.push_back(atoi(service.c_str()));
            }
            std::getline(file, service, ',');
        }
    }
    
    void parse_debug()
    {
        std::stringstream ss("939\n7,13,x,x,59,x,31,19,");
        std::string raw_early;
        std::string service;
        
        std::getline(ss, raw_early);
        earliest = atoi(raw_early.c_str());

        do
        {
            std::getline(ss, service, ',');
            if (service[0] != 'x' && service.size() > 0)
            {
                _buses.push_back(atoi(service.c_str()));
            }
        } while (service.size() > 0);
    }

    std::pair<int, int> best_id_delay() const
    {
        std::vector<int> delays;
        const auto func = [this](const int& bus)
        {
            return bus - (earliest % bus);
        };
        std::transform(_buses.begin(), _buses.end(), std::back_inserter(delays), func);
        
        const auto& min_it = std::min_element(delays.begin(), delays.end());
        const size_t offset = min_it - delays.begin();

        return std::make_pair(_buses[offset], *min_it);
    }

    long long find_part2(const long long start_t = 0, const int idx = 0) const
    {
        if (_buses[idx+1] - (start_t % _buses[idx+1]) == 1)
        {
            return (idx == _buses.size()-2) ? start_t : find_part2(start_t, idx+1);
        }
        else
        {
            return find_part2(start_t+1, 0);
        }
    }

private:
    std::string _filename;

    int earliest;
    std::vector<int> _buses;
};
