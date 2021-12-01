package main

import (
    "fmt"

    //"advent2020.com/main/day1"
    //"advent2020.com/main/day2"
    //"advent2020.com/main/day3"
    //"advent2020.com/main/day4"
    //"advent2020.com/main/day5"
    //"advent2020.com/main/day5"
    "advent2020.com/main/day6"
)

func main() {
    fmt.Println("[Advent of Code] *** 2020 ***")
    day := day6.NewDay6("./day6/input.txt")

    res := day.First()
    fmt.Printf("Day 6 part 1: %v\n", res)
}
