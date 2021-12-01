package day1

import (
    "os"
    "fmt"
    "strings"
    "strconv"
)

type Day1 struct {
}

var Solutions Day1

func (d* Day1) First() (int, int) {

    bin, err := os.ReadFile("./day1/input.txt")
    if err != nil {
        fmt.Printf("[Day1] Could not parse input file at : %v, %v\n", "input.txt", err)
        return 0, 0
    }

    nums := strings.Split(string(bin), "\n")
    nums = nums[:len(nums)-1]

    for _, strn := range nums {
        for _, strm := range nums {
            n, _ := strconv.Atoi(strn)
            m, _ := strconv.Atoi(strm)
            sum := n+m
            fmt.Printf("[LOL] checking %v + %v = %v", n, m, sum)

            if (sum == 2020) {
                return n, m
            }
        }
    }

    return 0, 0
}

func (d* Day1) Second() (int, int, int) {
    bin, err := os.ReadFile("./day1/input.txt")
    if err != nil {
        fmt.Printf("[Day1] Could not parse input file at : %v, %v\n", "input.txt", err)
        return 0, 0, 0
    }

    nums := strings.Split(string(bin), "\n")
    nums = nums[:len(nums)-1]

    for _, strn := range nums {
        for _, strm := range nums {
            for _, strw := range nums {
                n, _ := strconv.Atoi(strn)
                m, _ := strconv.Atoi(strm)
                w, _ := strconv.Atoi(strw)
                sum := n+m+w

                if (sum == 2020) {
                    return n, m, w
                }
            }
        }
    }

    return 0, 0, 0
}

