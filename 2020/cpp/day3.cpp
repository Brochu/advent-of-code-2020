#include <fstream>
#include <string>
#include <istream>
#include <vector>

class Day3
{
public:
    Day3(char* fname) : filename(fname) { }

    int count_trees(std::pair<int, int> deltas) const
    {
        std::ifstream file(filename);
        std::string line;
        std::vector<std::string> field;
        while(std::getline(file, line))
        {
            field.push_back(line);
        }
        file.close();

        int count = 0;
        int x = 0;
        for(int i = 0; i < field.size(); i += std::get<1>(deltas))
        {
            if (i >= field.size()) break;
            
            if (field[i][x] == '#')
            {
                count++;
            }
            x = (x + std::get<0>(deltas)) % field[i].size();
        }
        
        return count;
    }
    
private:
    std::string filename;
};
