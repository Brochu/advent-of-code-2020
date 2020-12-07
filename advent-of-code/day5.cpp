#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Day5
{
public:
    Day5(char* fname) : filename(fname)
    { }

    std::vector<int> list_seat_ids() const
    {
        // run algo on all elements of list_seats();
        return std::vector<int>();
    }

    std::vector<std::pair<int, int>> list_seats() const
    {
        std::vector<std::pair<int, int>> result;
        
        std::ifstream file(filename);
        file.close();

        return result;
    }

    std::pair<int, int> parse_seat(std::string seat) const
    {
        // Parsing for row
        int low_row = 0;
        int high_row = max_rows;
        
        // Parsing for col
        int low_col = 0;
        int high_col = max_cols;
        
        return std::make_pair(0, 0);
    }

private:
    std::string filename;
    const int max_rows = 127;
    const int max_cols = 7;
};
