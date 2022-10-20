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
        std::vector<int> results;
        const std::vector<std::pair<int, int>> seats = list_seats();

        std::transform(seats.cbegin(), seats.cend(), std::back_inserter(results),
            [](const std::pair<int, int>& seat){ return (std::get<0>(seat) * 8) + std::get<1>(seat); });
        return results;
    }

    std::vector<std::pair<int, int>> list_seats() const
    {
        std::vector<std::pair<int, int>> result;
        
        std::ifstream file(filename);
        std::string line;
        while(file)
        {
            std::getline(file, line);
            if (line.size() != 0)
            {
                const auto seat = parse_seat(line);
                result.push_back(seat);
            }
        }
        file.close();
        
        return result;
    }

    std::pair<int, int> parse_seat(std::string seat) const
    {
        int low_row = 0;
        int high_row = max_rows;
        
        int row = -1;
        size_t i = 0;
        for(i = 0; i < seat.size() - 4; ++i)
        {
            if (seat[i] == 'B') low_row += ((high_row - low_row) + 1) / 2;
            else if (seat[i] == 'F') high_row -= ((high_row - low_row) + 1) / 2;
        }
        row = (seat[i] == 'F') ? low_row : high_row;
        
        int low_col = 0;
        int high_col = max_cols;
        int col = -1;
        for(i = seat.size() - 3; i < seat.size() - 1; ++i)
        {
            if (seat[i] == 'R') low_col += ((high_col - low_col) + 1) / 2;
            else if (seat[i] == 'L') high_col -= ((high_col - low_col) + 1) / 2;
        }
        col = (seat[i] == 'L') ? low_col : high_col;
        
        return std::make_pair(row, col);
    }

private:
    std::string filename;
    const int max_rows = 127;
    const int max_cols = 7;
};
