#include <vector>
#include <unordered_map>
#include <set>

class Day15
{
public:
    Day15()
    {
        _start_num = {15,5,1,4,7,0}; // REAL INPUT
        //_start_num = {3,1,2}; // TEST INPUT
    }

    int64_t get_turn(int turn)
    {
        std::unordered_map<int64_t, int> history; // { value, turn }
        
        int64_t last = -1;
        int64_t curr = -1;
        
        for(int i = 0; i < turn; ++i)
        {
            if (i < _start_num.size()) curr = _start_num[i];
            else if (history.find(last) != history.end()) curr = i-history[last];
            else curr = 0;
            
            history[last] = i;
            last = curr;
        }
        
        return curr;
    }

private:
    std::vector<int> _start_num;
    
    
};
