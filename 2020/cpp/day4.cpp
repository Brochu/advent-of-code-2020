#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

class Day4
{
public:
    Day4(char* fname) : filename(fname)
    {
        _needed = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
        _eye_colors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
    }

    int count_valid_keys() const
    {
        int count = 0;
        
        std::ifstream file(filename);
        std::string line;
        std::vector<std::string> keys;
        bool valid = true;
        while(std::getline(file, line))
        {
            if (line.size() != 0)
            {
                std::stringstream l(line);
                std::string elem;
                std::string key;
                std::string value;
                const int keySize = 3;
                while(std::getline(l, elem, ' '))
                {
                    key = elem.substr(0, keySize);
                    value = elem.substr(keySize + 1, elem.size() - keySize + 1);
                    printf("(%s : %s)\n", key.c_str(), value.c_str());

                    // Can set valid here
                    // Apply parsing rules here
                    if (key == "byr")
                    {
                        const int birthyear = atoi(value.c_str());
                        valid &= birthyear >= 1920 && birthyear <= 2002;
                    }
                    else if (key == "iyr")
                    {
                        const int issueyear = atoi(value.c_str());
                        valid &= issueyear >= 2010 && issueyear <= 2020;
                    }
                    else if (key == "eyr")
                    {
                        const int expyear = atoi(value.c_str());
                        valid &= expyear >= 2020 && expyear <= 2030;
                    }
                    else if (key == "hgt")
                    {
                        std::stringstream height_ss(value);
                        int h;
                        height_ss >> h;
                        std::string unit;
                        height_ss >> unit;
                    
                        valid &= (unit == "cm" && h >= 150 && h <= 193) || (unit == "in" && h >= 59 && h <= 76);
                    }
                    else if (key == "hcl")
                    {
                        valid &= value[0] == '#' &&
                            std::all_of(++value.begin(), value.end(), [](const char c){ return isxdigit(c); });
                    }
                    else if (key == "ecl")
                    {
                        valid &= std::find(_eye_colors.begin(), _eye_colors.end(), value) != _eye_colors.end();
                    }
                    else if (key == "pid")
                    {
                        valid &= value.size() == 9 &&
                            std::all_of(value.begin(), value.end(), [](const char c){ return isdigit(c); });
                    }
                    
                    keys.push_back(key);
                }
            }
            else
            {
                if (std::all_of(_needed.begin(), _needed.end(),
                    [&keys](const std::string s) { return std::find(keys.begin(), keys.end(), s) != keys.end(); }) &&
                    valid)
                {
                    ++count;
                }
                printf("^^^^ %s ^^^^\n=======\n", (valid) ? "VALID" : "INVALID");
                
                keys.clear();
                valid = true;
            }
        }

        // Last case
        if (std::all_of(_needed.begin(), _needed.end(),
            [&keys](const std::string s) { return std::find(keys.begin(), keys.end(), s) != keys.end(); }) &&
            valid)
        {
            ++count;
        }
        
        file.close();

        return count;
    }
private:
    std::string filename;
    std::vector<std::string> _needed;
    std::vector<std::string> _eye_colors;
};
