package day2

import(
    "fmt"
    "os"
    "strings"
    "bufio"
)

type Day2 struct {
}

var Solutions Day2

func (d* Day2) First() int {
    data, _ := os.ReadFile("./day2/input.txt")
    s := bufio.NewScanner(strings.NewReader(string(data)))

    total := 0
    for s.Scan() {
        entry := s.Text()
        if len(entry) > 0 && isValid(entry) { total++ }
    }

    return total
}

func (d* Day2) Second() int {
    data, _ := os.ReadFile("./day2/input.txt")
    s := bufio.NewScanner(strings.NewReader(string(data)))

    total := 0
    for s.Scan() {
        entry := s.Text()
        if len(entry) > 0 && isValid2(entry) { total++ }
    }

    return total
}

func isValid(entry string) bool {

    min, max, letter, password := getElements(entry)
    count := 0

    for _, c := range password {
        if c == letter { count++ }
    }

    success := count >= min && count <= max
    fmt.Printf("%v > %v\n", entry, success)

    return success
}

func isValid2(entry string) bool {
    min, max, letter, password := getElements(entry)

    if string(password[min-1]) == string(letter) && string(password[max-1]) == string(letter) { return false }
    success := string(password[min-1]) == string(letter) || string(password[max-1]) == string(letter)
    fmt.Printf("%v > %v (%v | %v) %v\n", entry, password, string(password[min-1]), string(password[max-1]), success)

    return success
}

func getElements(entry string) (int, int, rune, string) {

    min, max, letter, password := 0, 0, ' ', ""

    _, err := fmt.Sscanf(entry, "%d-%d %c: %s", &min, &max, &letter, &password)
    if err != nil {
        fmt.Printf("[Day 2] error checking validity for line: %v\n%v\n", entry, err)
    }

    return min, max, letter, password
}

