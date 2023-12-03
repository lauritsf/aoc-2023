# Advent of Code 2023: Day 3 Solutions - Gear Ratios

Link to the [problem statement](https://adventofcode.com/2023/day/3).

## Part 1

### Objective

The objective is to find the numbers in the schematic, that have a number adjacent to a symbol (not a number or a dot).
The result will be the sum of all these numbers.

### Solution: [day3:cpp for Part 1](part1.cpp)

#### Approach

- A PartNumber is reperesented as an integer and a number of coordinates.
- The schematic can be efficiently represented as a 2D array of chars in an `EngineSchematic` class.
- A member function `EngineSchematic::getPartNumbers()` returns a vector of all part numbers in the schematic.
- Another member function `EngineSchematic::isAdjacentToSymbol()` checks if a `PartNumber` is adjacent to a symbol.
- The main function `main()` reads the schematic from the input file, and prints the sum of all part numbers that are adjacent to a symbol.

## Part 2

### Objective

We now need to find the gears and their gear ratios.
A gear is a character '*' in the schematic, which is adjacent to exactly two part numbers.

### Solution: [day3:cpp for Part 2](part2.cpp)

#### Approach

- I decided to not reuse the code from Part 1, and instead write a new solution.
- The schematic is read and represented as a `std::vector<std::string>`, faster to read and still easy to work with.
- We now represent the adjacent symbols in the `PartNumber`.
- We can then get all the gears from a map from gear coordinate to their adjacent numbers.
- We only keep the gears with exactly two adjacent numbers.

## Comment

Going forward, I will try to spend more time on designing the solution before coding it.
