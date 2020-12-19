#include <vector>
#include <map>
#include <set>

class Day15
{
public:
    Day15()
    {
        //_start_num = {15,5,1,4,7,0}; // REAL INPUT
        _start_num = {0,3,6}; // TEST INPUT

        // CHECK THIS
        for(int i = 0; i < _start_num.size(); ++i)
        {
            _history[_start_num[i]] = i+1;
        }
    }

    int64_t get_turn(int turn)
    {
        if (turn-1 < _start_num.size())
        {
            _history[_start_num[turn-1]] = turn;
            return _start_num[turn-1];
        }

        const int64_t last = get_turn(turn-1);
        if (_history.find(last) != _history.end() && _history[last] != turn-1)
        {
            // NEVER COMES HERE, WHEN TO UPDATE THE HISTORY??
            _history[turn-_history[last]] = turn;
            return turn-_history[last];
        }
        else
        {
            _history[0] = turn;
            return 0;
        }
    }

private:
    std::vector<int> _start_num;
    
    std::map<int64_t, int> _history; // { value, turn }
};
