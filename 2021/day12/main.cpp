#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::vector<std::string>> LinkMap;
typedef std::unordered_map<std::string, size_t> IndexMap;

#define PATH "./test_input.txt"
//#define PATH "./input.txt"
#define MAX_NODES 20

struct TrieNode
{
    TrieNode() : isEnd(false)
    {
    }

    TrieNode* next[MAX_NODES];
    bool isEnd;
};

TrieNode buildTrie(const LinkMap& linkDB, const IndexMap& lutIndex)
{
    TrieNode root;

    // Init next for root
    for (int i = 0; i < MAX_NODES; i++) root.next[i] = nullptr;
    // Recurse through to build trie

    return root;
}

//TODO: Add a set passed by copy that will keep the nodes visited by depth, to avoid lowercase more than once
void buildTrieImpl(TrieNode* n/*, ... */)
{
    //TODO: Check if we reached end node, if yes return
    //TODO: Get all possible next's
    //TODO: Create a new node at the right index of the array
    //TODO: Call Impl with the new node
}

int main(int argc, char** argv)
{
    auto file = std::ifstream(PATH);
    LinkMap linkDB;
    size_t index = 0;
    IndexMap lutIndex;
    std::set<std::string> nodes;

    std::string line;
    while (file >> line)
    {
        std::string from, to;
        const size_t idx = line.find('-');
        from = line.substr(0, idx);
        to = line.substr(idx + 1);

        printf("* %s -> %s\n", from.c_str(), to.c_str());

        linkDB[from].push_back(to);
        if (nodes.find(from) == nodes.end())
        {
            nodes.insert(from);
            lutIndex[from] = index++;
        }
        if (nodes.find(to) == nodes.end())
        {
            nodes.insert(to);
            lutIndex[to] = index++;
        }

        if (from != "start")
        {
            linkDB[to].push_back(from);
        }
    }

    //printf("\nNode count = %ld\n", nodes.size());
    //for (const std::string& n : nodes)
    //{
    //    printf("[%ld] Node %s :", lutIndex[n], n.c_str());
    //    for (const std::string& link : linkDB[n])
    //    {
    //        printf("%s, ", link.c_str());
    //    }
    //    printf("\n");
    //}

    TrieNode root = buildTrie(linkDB, lutIndex);

    //printf("Result = %i\n", 1337);
    return 0;
}
