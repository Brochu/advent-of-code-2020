#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

#include "Day20.cpp"

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
    //Day5 d(argv[1]);
    //auto result = d.list_seat_ids();
    //for(const auto& e : result)
    //{
    //    printf("%i\n", e);
    //}

    // Find max ID
    //const auto it = std::max_element(result.begin(), result.end());
    //printf("max seat id is = %i\n", *it);

    //std::sort(result.begin(), result.end());
    //for(int i = 0; i < result.size()-1; ++i)
    //{
    //    if (result[i] != result[i+1] - 1)
    //    {
    //        printf("%i\n", result[i+1]);
    //    }
    //}

    // Day 6
    //Day6 d(argv[1]);
    //const auto groups = d.list_groups();
    //std::vector<int> scores;
    //std::transform(groups.cbegin(), groups.cend(), std::back_inserter(scores),
    //    [&d](const auto& g){ return d.get_group_score_every(g); });

    //const int total = std::accumulate(scores.begin(), scores.end(), 0);
    //printf("Total count = %i\n", total);
    
    // Day 7
    //Day7 d(argv[1]);
    //const auto result = d.get_all_outermost("shiny gold bag");
    //printf("Bags count = %lld\n", result.size());

    //const int part2result = d.get_max_count("shiny gold bag");
    //printf("Bags count 2 = %i\n",  part2result);
    
    // Day 8
    //Day8 d(argv[1]);
    ////d.parse_debug("nop +0\nacc +1\njmp +4\nacc +3\njmp -3\nacc -99\nacc +1\njmp -4\nacc +6");
    //d.parse_file();
    //d.force_complete_run();

    //printf("value of the acc: %i\n", d.get_acc());
    
    // Day 9
    //Day9 d(argv[1]);
    ////d.init_from_debug(
    ////{
    ////        35,
    ////        20,
    ////        15,
    ////        25,
    ////        47,
    ////        40,
    ////        62,
    ////        55,
    ////        65,
    ////        95,
    ////        102,
    ////        117,
    ////        150,
    ////        182,
    ////        127,
    ////        219,
    ////        299,
    ////        277,
    ////        309,
    ////        576,
    ////});
    //d.init_from_file();
    //const int result = d.check_d1(25);
    //printf("found number: %i\n", result);
    //
    //const auto& list = d.check_d2(result);
    //for(const auto& i : list)
    //{
    //    printf("- %i\n", i);
    //}
    //
    //const auto& vals = std::minmax_element(list.cbegin(), list.cend());
    //int min = *std::get<0>(vals);
    //int max = *std::get<1>(vals);
    //printf("min: %i, max: %i\ntotal = %i\n", min, max, min + max);
    
    // Day 10
    //Day10 d(argv[1]);
    //d.init_from_file();
    ////d.init_from_debug();
    //
    //const int result = d.calculate_part1();
    //printf("Result for part 1 = %i\n", result);
    //
    //const long long part2 = d.calculate_part2();
    //printf("Result for part 1 = %lli\n", part2);
    
    // Day 11
    //Day11 d(argv[1]);
    //int run_count = 0;
    //while(d.run_once(false))
    //{
    //    printf("Running %i times ...\n", ++run_count);
    //}
    //d.output_map();

    //const auto total = d.count_occupied();
    //printf("total occupied = %lld\n",  total);
    
    // Day 12
    //Day12 d(argv[1]);
    //const int dist = d.get_man_dist();
    //printf("dist = %i\n", dist);
    
    // Day 13
    //Day13 d(argv[1]);
    //const auto& result = d.best_id_delay();
    //printf("best bus id = %i, delay = %i [%i]\n", result.first, result.second, result.first * result.second);

    //const auto& part2 = d.find_part2();
    //printf("result for part2 = %lld", part2);
    
    // Day 15
    //Day15 d;
    //const auto result = d.get_turn(30000000);
    //printf("[D15][P1][%i] %lld\n", 30000000, result);
    
    // Day 16
    //Day16 d(argv[1]);
    //const auto result = d.get_error_rate();
    //printf("ERROR RATE: %lld\n", result);

    //const auto part_2 = d.get_part_2();
    //printf("PART 2: %lld\n", part_2);
    
    // Day 17
    //Day17 d(argv[1]);
    //d.debug_print();
    //d.simulate(6);
    //printf("active count = %lld", d.active_count());
    
    // Day 18
    //Day18 d(argv[1]);
    //const auto& res = d.get_part1();
    //printf("= %lld\n", res);
    
    // Day 19
    //Day19 d(argv[1]);
    //const auto result = d.get_par1();
    //printf("\n");
    //printf(" = %i\n", result);

    // Day 20
    Day20 d(argv[1]);
    const auto result = d.solve();
    const int offset = static_cast<int>(sqrt(result.size())) - 1;
    
    const size_t corner1 = result.front();
    const size_t corner2 = *(result.begin()+offset);
    const size_t corner3 = *(result.rbegin()+offset);
    const size_t corner4 = result.back();

    const size_t total = corner1 * corner2 * corner3 * corner4;

    printf("corners: (%lld, %lld, %lld, %lld)\n", corner1, corner2, corner3, corner4);
    printf("total = %lld\n", total);

    return 0;
}
