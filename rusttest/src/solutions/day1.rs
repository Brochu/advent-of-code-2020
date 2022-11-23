pub fn solve_part_one(input: &str) -> u64 {

    for num1 in input.lines() {
        for num2 in input.lines() {
            if num1.len() > 0 && num2.len() > 0 {
                let n1 :u64 = num1.parse().unwrap();
                let n2 :u64 = num2.parse().unwrap();

                if n1 + n2 == 2020 {
                    return n1 * n2;
                }
            }
        }
    }

    return 0;
}

pub fn solve_part_two(input: &str) -> u64 {
    for num1 in input.lines() {
        for num2 in input.lines() {
            for num3 in input.lines() {
                if num1.len() > 0 && num2.len() > 0 && num3.len() > 0 {
                    let n1: u64 = num1.parse().unwrap();
                    let n2: u64 = num2.parse().unwrap();
                    let n3: u64 = num3.parse().unwrap();

                    if n1 + n2 + n3 == 2020 {
                        return n1 * n2 * n3;
                    }
                }
            }
        }
    }

    return 0;
}

#[cfg(test)]
mod tests {
    use super::*;
    use aoc::read_file;

    #[test]
    #[ignore]
    fn part_one() {
        let content = read_file("example", 1);
        assert_eq!(solve_part_one(&content), 514579);
    }

    #[test]
    #[ignore]
    fn part_two() {
        let content = read_file("example", 1);
        assert_eq!(solve_part_two(&content), 241861950)
    }
}
