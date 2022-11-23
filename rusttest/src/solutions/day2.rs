pub fn solve_part_one(input: &str) -> u64 {
    for line in input.lines() {
        let idx0 = line.find('-').unwrap();
        let min: u64 = line[0..idx0].parse().unwrap();

        let idx1 = line.find(' ').unwrap();
        let max: u64 = line[idx0+1..idx1].parse().unwrap();

        println!("{} - {}", min, max);
    }
    return 2;
}

pub fn solve_part_two(input: &str) -> u64 {
    println!("{}", input);
    return 2;
}

#[cfg(test)]
mod tests {
    use super::*;
    use aoc::read_file;

    #[test]
    fn part_one() {
        let content = read_file("example", 2);
        assert_eq!(solve_part_one(&content), 2);
    }

    #[test]
    fn part_two() {
        let content = read_file("example", 2);
        assert_eq!(solve_part_two(&content), 2)
    }
}
