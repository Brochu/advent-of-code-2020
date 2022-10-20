package day3

import(
    "fmt"
    "os"
    "strings"
    "bufio"
)

type Day3 struct {
}

var Solutions Day3

func (d* Day3) First() int {
    data, _ := os.ReadFile("./day3/input.txt")
    s := bufio.NewScanner(strings.NewReader(string(data)))

    parsed := make([]string, 0)
    for s.Scan() {
        parsed = append(parsed, s.Text())
    }

    return check(parsed, 3, 1)
}

func (d* Day3) Second() []int {
    data, _ := os.ReadFile("./day3/input.txt")
    s := bufio.NewScanner(strings.NewReader(string(data)))

    parsed := make([]string, 0)
    for s.Scan() {
        parsed = append(parsed, s.Text())
    }

    results := make([]int, 0)
    results = append(results, check(parsed, 1, 1))
    results = append(results, check(parsed, 3, 1))
    results = append(results, check(parsed, 5, 1))
    results = append(results, check(parsed, 7, 1))
    results = append(results, check(parsed, 1, 2))

    return results
}

func check(lines []string, leftAdd int, downAdd int) int {
    linesCount := len(lines)
    left := 0
    trees := 0

    for i := 0; i < linesCount; i += downAdd {
        c := lines[i][left]
        if string(c) == "#" { trees++ }

        fmt.Printf("[day3] pattern: %v [left=%v | %v]\n", lines[i], left, "#" == string(c))
        left = (left + leftAdd) % len(lines[i])
    }

    return trees
}

