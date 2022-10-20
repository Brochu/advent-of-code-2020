#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include <algorithm>

class Day2
{
public:
    Day2(char* fname) : filename(fname) { }

    int find_valid_count() const
    {
        std::ifstream file(filename);
        std::string line;

        int count = 0;
        
        int low, high;
        std::string passwd;
        char letter;
        while(file)
        {
            std::getline(file, line);
            std::stringstream stream(line);

            // Learn 2 scanf
            stream >> low;
            stream >> high;
            high *= -1;
            stream >> letter;
            stream >> passwd;
            stream >> passwd;

            const long long i = std::count_if(passwd.begin(), passwd.end(), [letter](char c){ return letter == c; });
            if (i >= low && i <= high)
            {
                count++;
            }
            
            std::printf("(%i, %i) - [%c] (%s) : seen = %lli; count = %i\n", low, high, letter, passwd.c_str(), i, count);
        }
        file.close();

        return count;
    }
    
    int find_valid_2() const
    {
        std::ifstream file(filename);
        std::string line;

        int count = 0;
        
        int low, high;
        std::string passwd;
        char letter;
        while(file)
        {
            std::getline(file, line);
            std::stringstream stream(line);

            // Learn 2 scanf
            stream >> low;
            stream >> high;
            high *= -1;
            stream >> letter;
            stream >> passwd;
            stream >> passwd;

            std::printf("%i, %i (%s)\n", low, high, passwd.c_str());

            if (low >= 0 && high >= 0)
            {
                if(passwd[low-1] == letter || passwd[high-1] == letter)
                {
                    if (passwd[low-1] != passwd[high-1])
                    {
                        count++;
                    }
                }
            }
        }
        file.close();

        return count;
    }
    
private:
    std::string filename;
};
