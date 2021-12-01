#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

class Day6
{
public:
    Day6(char* fname) : filename(fname)
    { }

    std::vector<std::vector<std::string>> list_groups() const
    {
        std::vector<std::vector<std::string>> groups;
        std::vector<std::string> people;
        std::ifstream file(filename);

        std::string line;
        while(file)
        {
            std::getline(file, line);
            if (line.size() == 0)
            {
                groups.push_back(people);
                people.clear();
            }
            else
            {
                people.push_back(line);
            }
        }
        
        file.close();
        return groups;
    }

    int get_group_score_any(std::vector<std::string> group) const
    {
        std::set<char> yes_ans;
        for(const auto& person : group)
        {
            for(const auto& ans : person)
            {
                yes_ans.insert(ans);
            }
        }
        return yes_ans.size();
    }
    
    int get_group_score_every(std::vector<std::string> group) const
    {
        int count = 0;
        for(const auto& question : "abcdefghijklmnopqrstuvwxyz")
        {
            const auto pred = [question](const std::string& s)
            { return std::find(s.begin(), s.end(), question) != s.end();  };
            
            if (std::all_of(group.begin(), group.end(), pred)) ++count;
        }
        return count;
    }

private:
    std::string filename;
};
