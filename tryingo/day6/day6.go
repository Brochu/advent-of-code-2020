package day6

import(
    "bufio"
    "fmt"
    "os"
    "strings"
)

type Day6 struct {
    Groups [][]string
}

func NewDay6(filename string) Day6 {
    fmt.Printf("[Day 6] Object ready\n")

    var d Day6
    d.Groups = make([][]string, 0)
    buffer := make([]string, 0)

    data, _ := os.ReadFile(filename)
    s := bufio.NewScanner(strings.NewReader(string(data)))
    for s.Scan() {
        if len(s.Text()) == 0 {
            d.Groups = append(d.Groups, buffer)
        } else {
            buffer = append(buffer, s.Text())
        }
    }

    return d
}

func (d* Day6) First() int {
    fmt.Printf("[Day 6] Computing the result for first part ...\n")

    for _, g := range d.Groups {
        for j, p := range g {
            fmt.Printf("[Day 6] %v | %v\n", j, p)
        }
        fmt.Println()
    }

    return 0
}

func (d* Day6) Second() int {
    fmt.Printf("[Day 6] Computing the result for second part ...\n")
    return 0
}

