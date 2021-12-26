#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#define PATH "./input.txt"

static std::unordered_map<char, short> lutHex
{
    { '0', 0 },
    { '1', 1 },
    { '2', 2 },
    { '3', 3 },
    { '4', 4 },
    { '5', 5 },
    { '6', 6 },
    { '7', 7 },
    { '8', 8 },
    { '9', 9 },
    { 'A', 10 },
    { 'B', 11 },
    { 'C', 12 },
    { 'D', 13 },
    { 'E', 14 },
    { 'F', 15 },
};

std::string parseFile(std::ifstream&& file)
{
    std::string line;
    getline(file, line);
    return line;
}

void debugBits(const std::vector<bool>& bits, int start, int length)
{
    printf("[DEBUG] ");
    for (int i = start; i < (start + length); i++)
    {
        if ((i % 4) == 0 && i != 0)
            printf("%s ", bits[i] ? "1" : "0");
        else
            printf("%s", bits[i] ? "1" : "0");
    }
    printf("\n");
}

std::vector<bool> parseBits(const std::string& line)
{
    std::vector<bool> result;

    for (const char& c : line)
    {
        short value = lutHex[c];
        //printf("[BITS] character = %c; value = %i >> ", c, value);
        for (int i = 3; i >= 0; i--)
        {
            bool b = ((value >> i) % 2) != 0;
            //printf("%s", b ? "1" : "0");

            result.push_back(b);
        }
        //printf("\n");
    }

    //debugBits(result);
    return result;
}

unsigned long getValue(const std::vector<bool>& bits, int& start, int length)
{
    unsigned long value = 0;
    for (int i = 0; i < length; i++)
    {
        value <<= 1;
        value += bits[start++];
    }
    return value;
}

struct Header
{
    short version = 0;
    short type = 0;
};
Header fetchHeader(const std::vector<bool>& bits, int& start)
{
    short ver = 0;
    for (int i = 0; i < 3; i++)
    {
        ver <<= 1;
        ver += bits[start++];
    }

    short type = 0;
    for (int i = 0; i < 3; i++)
    {
        type <<= 1;
        type += bits[start++];
    }

    return { ver, type };
}

struct LiteralPart
{
    bool isEnd = false;
    unsigned long value = 0;
};
LiteralPart fetchNextPart(const std::vector<bool>& bits, int& start)
{
    bool isEnd = bits[start++];
    unsigned long value = getValue(bits, start, 4);

    return { !isEnd, value };
}

unsigned long parsePacket(const std::vector<bool>& packet, int& start, unsigned long& totalVersions)
{
    // Get Header
    Header h = fetchHeader(packet, start);
    printf("[PACKET] Header: version = %i; type = %i\n", h.version, h.type);
    totalVersions += h.version;

    if (h.type == 4)
    {
        LiteralPart part;
        unsigned long finalVal = 0;
        while (!part.isEnd)
        {
            part = fetchNextPart(packet, start);
            printf("[PACKET] Part: isEnd = %s; value = %ld\n", part.isEnd ? "TRUE" : "FALSE", part.value);

            finalVal <<= 4;
            finalVal |= part.value;
        }

        printf("[PACKET] Final literal = %ld\n", finalVal);
        return finalVal;
    }
    else
    {
        bool parseType = packet[start++];
        std::vector<unsigned long> results;

        if (parseType)
        {
            unsigned long count = getValue(packet, start, 11);
            printf("[PACKET] Sub Packets Count = %ld\n", count);

            for (int i = 0; i < count; i++)
            {
                results.push_back(parsePacket(packet, start, totalVersions));
            }
        }
        else
        {
            unsigned long length = getValue(packet, start, 15);
            printf("[PACKET] Bit Length = %ld\n", length);

            unsigned long target = start + length;
            while (start < target)
            {
                results.push_back(parsePacket(packet, start, totalVersions));
            }
        }

        switch (h.type)
        {
        case 0:
            // SUM
            return
        case 1:
            // PRODUCT
            return 0;
        case 2:
            // MIN
            return 0;
        case 3:
            // MAX
            return 0;
        case 5:
            // GREATER THAN
            return 0;
        case 6:
            // LESS THAN
            return 0;
        case 7:
            // EQUAL TO (always 2 sub packs)
            return 0;
        default:
            // What??!
            return -1;
        }
    }

    // This should not happen...
    return -1;
}

int main(int argc, char** argv)
{
    // Get the string in the file, or hardcode one for debug
    /*
    std::ifstream file = std::ifstream(PATH);
    std::string line;
    getline(file, line);
    */

    std::string line = "C200B40A82";

    const std::vector<bool> bits = parseBits(line);
    int start = 0;
    unsigned long totalVersions = 0;
    parsePacket(bits, start, totalVersions);

    printf("\nResult = %ld\n", totalVersions);
    return 0;
}
