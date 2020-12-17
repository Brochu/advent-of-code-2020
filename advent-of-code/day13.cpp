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
        int t = 0;
        while(file)
        {
            if (service[0] != 'x')
            {
                _buses.push_back(atoi(service.c_str()));
                _bus2.push_back(std::make_pair(t, atoi(service.c_str())));
            }
            else
            {
                _buses.push_back(-1);
            }
            ++t;
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

        int t = 0;
        do
        {
            std::getline(ss, service, ',');
            if (service.size() > 0 && service[0] != 'x')
            {
                _buses.push_back(atoi(service.c_str()));
                _bus2.push_back(std::make_pair(t, atoi(service.c_str())));
            }
            ++t;
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
        long long i = _bus2[0].second, t = 1;
        long long nxt_i = _bus2[0].second;
        for (int j = 0; j < _bus2.size()-1; ++j) {
            long long t = 1;
            while(true) {
                long long t1 = (i + (nxt_i * t));
                auto next_b = t1 + _bus2[j+1].first;
                if((next_b % _bus2[j+1].second) ==0) {
                    i = t1;
                    break;
                }
                t++;
            }
            nxt_i *= _bus2[j+1].second;
        }

        return i;
    }

private:
    std::string _filename;

    int earliest;
    std::vector<int> _buses;
    std::vector<std::pair<int, long>> _bus2;
};
