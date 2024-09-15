#include <cstring>
#include <fstream>
#include <string>

enum Type { GROUP, LEAF };

struct Rule {
    Type type;
    union {
        char val;
        int refs[5];
    };
    size_t len;
};

class Day19
{
public:
    Day19(std::string fname) : _filename(fname) {
        std::fstream f(fname);
        std::string line;
        while(std::getline(f, line)) {
            auto pos = line.find(':');
            if (pos == line.npos) {
                break;
            }
            std::string idstr = line.substr(0, pos);
            int id = atoi(idstr.c_str());

            std::string rest = line.substr(pos + 2);
            printf("id: %s ; rest: %s\n", idstr.c_str(), rest.c_str());
            //TODO: READ RULES

            _rules[id] = Rule { LEAF };
        }
        f.close();
    }

    size_t get_part1() {
        return 69;
    }

private:
    std::string _filename;
    Rule _rules[256];
};
