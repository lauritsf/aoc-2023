# Advent of Code 2023: Day 4 Solutions - Scratchcards

Link to the [problem statement](https://adventofcode.com/2023/day/4)

## Part 1

### Objective

We need to help the elf to figure out how many point each scratchcard is worth.
The first winning number is worth 1 point, while each subsequent winning number doubles the points.

### Solution: [day4:cpp for Part 1](part1.cpp)

#### Approach

- Initialize `totalPoints` to 0.
- For each line:
  - Read winning numbers and scratchcard numbers.
  - Winning numbers and our numbers are stored as a set of integers.
  - The number of matches is the size of the intersection of the two sets.
  - if the number of matches is greater than 0:
    - `points` is 2 to the power of the number of matches minus 1.
    - `totalPoints` is incremented by `points`.
- Print `totalPoints`.

## Part 2

### Objective

It seems there is no such thing as "Points".
A match will instead cause you to win more scratchcards of the ones below it.
Eg. if you match 3 numbers on card 6, you with the 3 scratchcards below it (7, 8, 9).
The goal is to find the number of you end up with.

### Solution: [day4:cpp for Part 2](part2.cpp)

#### Approach

- We will represent the scratchcards a struct `Scratchcard` with `id` and `winCount` fields.
- Separately, we will keep track of the number of scratchcards we have for each card in an `std::unordered_map<int, int> cardCounts`.
- We start with 1 of each scratchcard.
- We will then iteratively go through each card and update the `cardCounts` map.
