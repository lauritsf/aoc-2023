# Advent of Code 2023: Day 1 Solutions - "Trebuchet?!"

Link to the [problem statement](https://adventofcode.com/2023/day/1).

## Part 1: Finding and adding numbers

### Objective

The task is to extract the first and last digit from each line of the input, combine them into a two-digit number, and calculate the sum of these numbers.

### Solution: [day1:cpp for Part 1](part1.cpp)

#### Approach

- Input is read line by line.
- For each line, the `first_digit` is updated once, and `last_digit` is updated for each valid digit found.
- `first_digit` and `last_digit` are combined into a two-digit number and added to a running sum.

#### Note

- While iterating in reverse could be more efficient for finding the `last_digit`, I decided to iterate over the entire line for simplicity.

## Part 2: Handling Written Numbers

### Objective

The challenge now includes processing written number names (e.g., "one", "two") in the input.

### Solution: [day1:cpp for Part 2](part2.cpp)

#### Approach

- I use a `std::map` to associate written number names with their numerical values.
- When a character is not a digit (checked using `isdigit`), the algorithm checks for a match with a written number name in the map.
- The number-word is converted with a function `convertWordToDigit`.
- The `first_digit` and `last_digit` are updated as in Part 1.

#### Note

- I could have used a `std::unordered_map` for faster lookup, but I decided to use a `std::map` to maintain the order of the written number names.

#### Challenges Encountered

- I initially had issues due to overlapping digit names in the input (e.g., "sevenine" representing 79). This was easily fixed by always iterating a single character instead of the length of the number-word.
