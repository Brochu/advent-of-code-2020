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
        parse_file();
        //parse_debug();
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
            else
            {
                _buses.push_back(-1);
            }
            std::getline(file, service, ',');
        }
    }
    
    void parse_debug()
    {
        std::stringstream ss("939\n1789,37,47,1889,");
        std::string raw_early;
        std::string service;
        
        std::getline(ss, raw_early);
        earliest = atoi(raw_early.c_str());

        do
        {
            std::getline(ss, service, ',');
            if (service.size() > 0 && service[0] != 'x')
            {
                _buses.push_back(atoi(service.c_str()));
            }
            else if (service.size() > 0 && service[0] == 'x')
            {
                _buses.push_back(-1);
            }
        } while (service.size() > 0);
    }

    std::pair<int, int> best_id_delay() const
    {
        std::vector<int> delays;
        const auto func = [this](const int& bus)
        {
            return (bus > 0) ? bus - (earliest % bus) : std::numeric_limits<int>::max();
        };
        std::transform(_buses.begin(), _buses.end(), std::back_inserter(delays), func);
        
        const auto& min_it = std::min_element(delays.begin(), delays.end());
        const size_t offset = min_it - delays.begin();

        return std::make_pair(_buses[offset], *min_it);
    }

    long long find_part2()
    {
        long long start = _buses[0];
        long long next = _buses[0];
        int target = 1;

        for(int i = 1; i < _buses.size(); ++i)
        {
            if (_buses[i] > 0)
            {
                while(_buses[i] - (start % _buses[i]) != target)
                {
                    printf("Tried for bus %i, starting at %lld next is %lld and target is %i\n",
                        _buses[i], start, next, target);
                    
                    start += next;
                }
                target++;
                next *= _buses[i];
            }
            else
            {
                ++target;
            }
        }
        
        return start;
    }

private:
    std::string _filename;

    int earliest;
    std::vector<int> _buses;
};
