package day4

import(
    "bufio"
    //"encoding/hex"
    "fmt"
    "os"
    "strings"
    "strconv"
)

type Day4 struct {
}

func NewDay4(filename string) int {

    lines := make(chan []string)
    acc := make(chan int)
    done := make(chan int)
    go reader(filename, lines)
    go validator(lines, acc, done)
    go accumulator(acc, done)

    <- done
    result := <- done

    return result
}

func (d* Day4) First() int {
    return 0
}

func reader(filename string, lines chan<- []string) {
    data, _ := os.ReadFile(filename)
    s := bufio.NewScanner(strings.NewReader(string(data)))
    temp := make([]string, 0)

    for s.Scan() {
        if len(s.Text()) > 0 {
            temp = append(temp, s.Text())
        } else {
            lines <- temp
            temp = nil
        }
    }

    close(lines)
}

func validator(in <-chan []string, acc chan<- int, done chan<- int) {

    for lines := range in {
        keys, ok := createKeyMap(lines)

        if ok && validateKeys(keys) {
            acc <- 1
        } else {
            acc <- 0
        }
    }

    close(acc)
    done <- 0
}

func createKeyMap(lines []string) (map[string]interface{}, bool) {
    keys := make(map[string]interface{})
    isValid := true

    for _, line := range lines {

        entries := strings.Split(line, " ")
        for _, entry := range entries {
            key := entry[0:3]
            rawValue := entry[4:]

            value, ok := parseValue(key, rawValue)
            isValid = isValid && ok
            keys[entry[0:3]] = value
        }
    }

    fmt.Printf("[Day 4] Creating key map > %v\n", isValid)
    fmt.Println("---------")

    return keys, isValid
}

func parseValue(key string, rawValue string) (interface{}, bool) {
    var result interface{}
    result = rawValue;
    isValid := true

    switch {
        case key == "byr":
            result, _ = strconv.Atoi(rawValue)
            isValid = result.(int) >= 1920 && result.(int) <= 2002
        case key == "iyr":
            result, _ = strconv.Atoi(rawValue)
            isValid = result.(int) >= 2010 && result.(int) <= 2020
        case key == "eyr":
            result, _ = strconv.Atoi(rawValue)
            isValid = result.(int) >= 2020 && result.(int) <= 2030
        case key == "hgt":
            result, _ = strconv.Atoi(rawValue[0:len(rawValue)-2])
            unit := rawValue[len(rawValue)-2:]
            switch {
                case unit == "in" :
                    isValid = result.(int) >= 59 && result.(int) <= 76
                case unit == "cm" :
                    isValid = result.(int) >= 150 && result.(int) <= 193
                default :
                    isValid = false
            }
        case key == "hcl":
            isValid = rawValue[0:1] == "#"
            if isValid {
                //_, ok := hex.DecodeString(rawValue[1:])
                //isValid = ok != nil
                isValid = isValid && len(rawValue[1:]) == 6
            }
        case key == "ecl":
            isValid = rawValue == "amb" ||
                        rawValue == "blu" ||
                        rawValue == "brn" ||
                        rawValue == "gry" ||
                        rawValue == "grn" ||
                        rawValue == "hzl" ||
                        rawValue == "oth"
        case key == "pid":
            isValid = len(rawValue) == 9
    }

    fmt.Printf("[%v | %v]= result: %v; isValid: %v =\n", key, rawValue, result, isValid)
    // Default case... only for CID as far as I know
    return result, isValid
}

func validateKeys(keys map[string]interface{}) bool {
    required := []string { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" }

    isValid := true
    for _, r := range required {
        _, ok := keys[r]
        isValid = isValid && ok
    }

    return isValid
}

func accumulator(acc <-chan int, done chan<- int) {
    total := 0
    for a := range acc {
        total = total + a
    }

    done <- total
}

