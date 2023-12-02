# Advent of Code 2023: Day 2 Solutions - "Cube Conundrum"

Link to the [problem statement](https://adventofcode.com/2023/day/2).

## Part 1

### Objective

In this problem we need to figure out which game result lines are possible given a total number of cubes for each color.

### Solution: [day2:cpp for Part 1](part1.cpp)

#### Approach

- We can store the color counts in a `struct` and then use a `std::vector` to store the color_counts for each game result.
- By creating a class `GameResult` we can create a constructor that takes a string and parses it into the game id and the color counts.
- We can then create a public function `is_possible` that takes a `ColorCounts` struct for total number of cubes of each color, and returns a boolean indicating whether the game result is possible.
- We can determine whether a game result is possible by checking if any of the color counts in the game result are greater than the total number of cubes of that color.

## Part 2

### Objective

We now need to figure out the minimum number of cubes of each color that would make the game result possible.

### Solution: [day2:cpp for Part 2](part2.cpp)

#### Approach

- We can use the same `GameResult` class as in Part 1.
- We will make a new member function `cubesNeeded`, which returns a `ColorCounts` struct for the minimum number of cubes of each color needed to make the game result possible.
- Taking the product of each color count in the `ColorCounts` and summing them gives us our result.
