#include <string>
#include <fstream>
#include <set>
#include <tuple>
#include <vector>

class Day1
{
public:
    Day1(char* filename, int t)
    {
        fname = filename;
        target = t;
    }

    std::pair<int, int> find_two() const
    {
        std::set<int> viewed;
        std::ifstream file(fname);

        int number;
        int diff;
        while(file >> number)
        {
            diff = target - number;
            if (viewed.find(diff) != viewed.end() && diff != number)
            {
                return std::make_pair(number, diff);
            }

            viewed.emplace(number);
        }

        file.close();
        return std::make_pair(0, 0);
    }
    
    std::tuple<int, int, int> find_three() const
    {
        std::vector<int> N;
        // int K = 3; // Pick 3 numbers that sum to target
        
        std::ifstream file(fname);
        int number;
        while(file >> number)
        {
            N.push_back(number);
        }
        file.close();

        // std::vector<std::vector<std::vector<bool>>> A;
        // for(int i = 0; i < N.size(); ++i)
        // {
        //     for(int j = 0; j <= target; ++j)
        //     {
        //         for(int k = 0; k <= K; ++k)
        //         {
        //         }
        //     }
        // }
        for (int i = 0; i < N.size(); ++i)
        {
            for (int j = 0; j < N.size(); ++j)
            {
                for (int k = 0; k < N.size(); ++k)
                {
                    if (N[i] + N[j] + N[k] == target)
                    {
                        return std::make_tuple(N[i], N[j], N[k]);
                    }
                }
            }
        }
        return std::make_tuple(0, 0, 0);
    }

private:
    std::string fname;
    int target;
};