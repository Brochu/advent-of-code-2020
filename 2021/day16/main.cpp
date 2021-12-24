#include <fstream>
#include <iostream>
#include <iterator>
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

void debugBits(const std::vector<bool>& bits)
{
    printf("[DEBUG] ");
    for (int i = 0; i < bits.size(); i++)
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

    debugBits(result);
    return result;
}

unsigned long getValue(std::vector<bool>&& bits)
{
    unsigned long value = 0;

    for (const bool& b : bits)
    {
        value <<= 1;
        value += b ? 1 : 0;
    }
    return value;
}

struct Header
{
    short version = 0;
    short type = 0;
};
Header fetchHeader(std::vector<bool>&& headerBits)
{
    auto start = headerBits.begin();
    auto end = headerBits.begin();

    std::advance(end, 3);
    short ver = (short)getValue(std::vector<bool>(start, end));

    start = end;
    std::advance(end, 3);
    short type = (short)getValue(std::vector<bool>(start, end));

    return { ver, type };
}

struct LiteralPart
{
    bool isEnd = false;
    unsigned long value = 0;
};
LiteralPart fetchNextPart(std::vector<bool>&& literalBits)
{
    debugBits(literalBits);

    auto start = literalBits.begin();
    std::advance(start, 1);
    auto end = literalBits.begin();
    std::advance(end, 5);

    return { !literalBits[0], getValue(std::vector<bool>(start, end)) };
}

unsigned long parsePacket(std::vector<bool> packet)
{
    // Get Header
    auto start = packet.begin();
    auto end = packet.begin();
    std::advance(end, 6);
    Header h = fetchHeader(std::vector<bool>(start, end));
    printf("[PACKET] Header: version = %i; type = %i\n", h.version, h.type);

    if (h.type == 4)
    {
        LiteralPart part;
        unsigned long finalVal = 0;
        while (!part.isEnd)
        {
            start = end;
            std::advance(end, 5);
            part = fetchNextPart(std::vector<bool>(start, end));
            printf("[PACKET] Part: isEnd = %s; value = %ld\n", part.isEnd ? "TRUE" : "FALSE", part.value);

            finalVal <<= 4;
            finalVal |= part.value;
        }

        printf("[PACKET] Final literal = %ld\n", finalVal);
    }
    else
    {
        start = end;
        bool parseType = *start;

        std::advance(start, 1);
        end = start;

        if (parseType)
        {
            std::advance(end, 11);
            unsigned long count = getValue(std::vector<bool>(start, end));
            printf("[PACKET] Sub Packets Count = %ld\n", count);

            start = end;
            end = packet.end();
            for (int i = 0; i < count; i++)
            {
                auto endIdx = parsePacket(std::vector<bool>(start, end));
                std::advance(start, endIdx);
            }
        }
        else
        {
            std::advance(end, 15);
            unsigned long length = getValue(std::vector<bool>(start, end));
            printf("[PACKET] Bit Length = %ld\n", length);

            unsigned long total = 0;

            start = end;
            end = packet.end();
            while (length > total)
            {
                auto endIdx = parsePacket(std::vector<bool>(start, end));
                std::advance(start, endIdx);

                total += endIdx;
            }
        }
    }

    return end - packet.begin();
}

int main(int argc, char** argv)
{
    // Get the string in the file, or hardcode one for debug
    /*
    std::ifstream file = std::ifstream(PATH);
    std::string line;
    getline(file, line);
    */

    //std::string line = "D2FE28";
    std::string line = "38006F45291200";
    //std::string line = "EE00D40C823060";

    std::vector<bool> bits = parseBits(line);
    auto endPos = parsePacket(std::vector<bool>(bits.begin(), bits.end()));

    printf("\nResult = %ld\n", 0L);
    return 0;
}
