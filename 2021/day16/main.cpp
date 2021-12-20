#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#define PATH "./test_input.txt"
//#define PATH "./input.txt"

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

std::bitset<6> fetchHeader(const std::string& raw, int& endPos)
{
    std::bitset<6> header;

    header |= lutHex[raw[0]];
    header <<= 2;
    header |= (raw[1] & (3 << 2)) >> 2;

    endPos = 6;
    return header;
}

std::bitset<5> fetchNextSegment(const std::string& raw, int& pos)
{
    std::bitset<5> segment;


    int group = pos / 4;
    int idx = pos % 4;
    printf("[SEGMENT] group: %i, index: %i\n", group, idx);

    std::bitset<8> temp;
    temp |= lutHex[raw[group]];
    temp <<= 4;
    temp |= lutHex[raw[group+1]];
    printf("[SEGMENT] temp = %s\n", temp.to_string().c_str());

    int first = 4 - idx;
    int mask = 0; //TODO: Build mask based off of first value, we want to catch the last 'first' bits in group byte
    int left = 5 - first;
    int shift = 4 - left;
    printf("[SEGMENT] first: %i, left: %i\n", first, left);

    segment |= (lutHex[raw[group]]) & first;
    segment <<= left;
    segment |= (lutHex[raw[group+1]]) >> shift;

    pos += 5;
    return segment;
}

struct Header
{
    short ver;
    short type;
};
Header parseHeader(std::bitset<6> bin)
{
    Header h;

    h.ver = (bin >> 3).to_ulong();
    bin &= 7;
    h.type = bin.to_ulong();

    return h;
}

int main(int argc, char** argv)
{
    std::ifstream file = std::ifstream(PATH);
    int pos = 0;
    std::string packet = parseFile(std::move(file));

    Header h = parseHeader(fetchHeader(packet, pos));
    printf("ver: %i; type: %i, next pos = %i\n", h.ver, h.type, pos);

    auto test = fetchNextSegment(packet, pos);
    printf("Got segment: %s\n", test.to_string().c_str());

    auto test1 = fetchNextSegment(packet, pos);
    printf("Got segment: %s\n", test1.to_string().c_str());

    auto test2 = fetchNextSegment(packet, pos);
    printf("Got segment: %s\n", test2.to_string().c_str());

    printf("\nResult = %ld\n", 0L);
    return 0;
}
