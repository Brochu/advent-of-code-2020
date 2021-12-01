package day5

import(
    "bufio"
    "fmt"
    "os"
    "sort"
    "strings"
)

type Day5 struct {
    Passes []string
    Count int
}

func NewDay5(filename string) Day5 {
    var d Day5
    d.Passes = make([]string, 0)
    d.Count = 0

    data, _ := os.ReadFile(filename)
    s := bufio.NewScanner(strings.NewReader(string(data)))
    for s.Scan() {
        d.Passes = append(d.Passes, s.Text())
        d.Count++
    }

    fmt.Printf("[Day 5] Object ready with %v passes ...\n", d.Count)
    return d
}

func (d* Day5) First() int {
    fmt.Printf("[Day 5] Computing the result for first part ...\n")

    highest := 0
    for _, pass := range d.Passes {
        row, col := FindSeatPos(pass)
        id := computeSeatId(row, col)

        if id > highest {
            highest = id
        }
    }

    return highest
}

func (d* Day5) Second() int {
    fmt.Printf("[Day 5] Computing the result for second part ...\n")

    ids := make([]int, 0)
    for _, pass := range d.Passes {
        row, col := FindSeatPos(pass)
        ids = append(ids, computeSeatId(row, col))
    }

    sort.Ints(ids)
    for i := 1; i < len(ids); i++ {
        current := ids[i]
        match := ids[i-1]

        if current != match + 1 {
            return match + 1
        }
    }

    return -1
}

func FindSeatPos(passText string) (int, int) {
    minR, maxR, minC, maxC := 0, 127, 0, 7

    for _, rune :=  range passText {
        c := string(rune)

        switch {
        case c == "F":
            mid := (maxR - minR) / 2
            maxR -= mid
            break;
        case c == "B":
            mid := ((maxR - minR) + 1) / 2
            minR += mid
            break;

        case c == "L":
            mid := ((maxC - minC) + 1) / 2
            maxC -= mid
            break;
        case c == "R":
            mid := ((maxC - minC) + 1) / 2
            minC += mid
            break;
        }
    }

    finalCol := 0
    if string(passText[len(passText)-1]) == "L" {
        finalCol = minC
    } else {
        finalCol = maxC
    }

    return minR, finalCol
}

func computeSeatId(row int, col int) int {
    return (row * 8) + col
}

