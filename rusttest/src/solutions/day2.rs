#[derive(Debug)]
struct Entry<'a> {
    min: usize,
    max: usize,
    letter: char,
    password: &'a str,
}

fn parse_range(input: &str) -> (usize, usize) {
    let vals: Vec<usize> = input.split("-")
        .map(|e| e.parse().unwrap())
        .collect();

    return (vals[0], vals[1]);
}

fn to_entry(input: &str) -> Entry {
    let elements: Vec<&str> = input.split(' ').collect();
    let (min, max) = parse_range(elements[0]);

    return Entry {
        min,
        max,
        letter: elements[1].chars().nth(0).unwrap(),
        password: elements[2],
    };
}

fn validate(e: &Entry) -> bool {
    println!("{:?}", e);

    let count = e.password.chars()
        .filter(|&c| c == e.letter)
        .count();

    return count >= e.min && count <= e.max;
}

pub fn solve_part_one(input: &str) -> usize {
    let valid_count = input.lines()
        .map(|line| to_entry(&line))
        .filter(|entry| validate(entry))
        .count();

    return valid_count;
}

pub fn solve_part_two(input: &str) -> u64 {
    println!("{}", input);
    return 2;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part_one() {
        let input = include_str!("../../example/day2.txt");
        assert_eq!(solve_part_one(&input), 2);
    }

    #[test]
    #[ignore]
    fn part_two() {
        let input = include_str!("../../example/day2.txt");
        assert_eq!(solve_part_two(&input), 2)
    }
}
