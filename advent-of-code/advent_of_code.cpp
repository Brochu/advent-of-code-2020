#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

#include "Day5.cpp"

int main(int argc, char* argv[])
{
    // Day 1
    // Day1 d(argv[1], 2020);
    // auto result = d.find_three();
    // const int num1 = std::get<0>(result);
    // const int num2 = std::get<1>(result);
    // const int num3 = std::get<2>(result);
    //
    // std::printf("Got result -> %i + %i + %i = %i\n\t%i * %i * %i = %i",
    //     num1, num2, num3, num1+num2+num3,
    //     num1, num2, num3, num1*num2*num3);

    // Day 2
    // Day2 d(argv[1]);
    // const auto result = d.find_valid_2();
    //
    // std::printf("Valid count: %i", result);

    // Day3
    //Day3 d(argv[1]);
    //
    //const auto result = d.count_trees(std::make_pair(3, 1));
    //std::printf("Tree count: %i\n", result);

    //std::vector<std::pair<int, int>> slopes = {
    //    std::make_pair(1, 1),
    //    std::make_pair(3, 1),
    //    std::make_pair(5, 1),
    //    std::make_pair(7, 1),
    //    std::make_pair(1, 2)
    //};
    //
    //std::vector<int> results;
    //results.reserve(slopes.size());
    //std::transform(slopes.begin(), slopes.end(), std::back_inserter(results),
    //    [&d](std::pair<int, int> p){ return d.count_trees(p); });
    //for(int i = 0; i < results.size(); ++i)
    //{
    //    printf("(%i, %i) -> %i\n", std::get<0>(slopes[i]), std::get<1>(slopes[i]), results[i]);
    //}

    //const auto total = std::accumulate(results.begin(), results.end(), 1, std::multiplies<int>());
    //printf("final -> %i", total);

    // Day 4
    // Day4 d(argv[1]);
    // const auto result = d.count_valid_keys();

    // printf("Valid count -> %i", result);
    
    // Day 5
    Day5 d(argv[1]);
    const auto result = d.list_seat_ids();

    // Find max ID
    
    return 0;
}
