#include <fstream>
#include <string>
#include <vector>

typedef std::pair<long, long> Point;

#define PATH "./input.txt"
//#define PATH "./test_input.txt"

struct Target
{
    Point xrange;
    Point yrange;

    Target(std::ifstream&& file)
    {
        long lowx, highx;
        file.ignore(15);
        file >> lowx;
        file.ignore(2);
        file >> highx;
        xrange = std::make_pair(lowx, highx);

        long lowy, highy;
        file.ignore(4);
        file >> lowy;
        file.ignore(2);
        file >> highy;
        yrange = std::make_pair(lowy, highy);
    }

    void print() const
    {
        printf("(%ld,%ld) : (%ld,%ld)\n", xrange.first, xrange.second, yrange.first, yrange.second);
    }

    long ycmp(long y)
    {
        if (y >= yrange.first && y <= yrange.second) return 0;
        else if (y < yrange.first) return -1;
        else return 1;
    }

    long xcmp(long x)
    {
        if (x >= xrange.first && x <= xrange.second) return 0;
        else if (x < xrange.first) return -1;
        else return 1;
    }
};

int main(int argc, char** argv)
{
    Target target(std::ifstream(PATH));
    target.print();

    //for (int i = 10; i > -20; i--)
    //{
    //    printf("[%i] cmp = %ld\n", i, target.ycmp(i));
    //}
    //for (int i = 0; i < 35; i++)
    //{
    //    printf("[%i] cmp = %ld\n", i, target.xcmp(i));
    //}
    long yvel = 67;
    long ypos = 0;
    while (target.ycmp(ypos) >= 0)
    {
        printf("[Y] pos = %ld; vel = %ld; cmp = %ld\n", ypos, yvel, target.ycmp(ypos));

        ypos += yvel;
        yvel--;
    }
        printf("[Y] pos = %ld; vel = %ld; cmp = %ld\n", ypos, yvel, target.ycmp(ypos));

    return 0;
}
