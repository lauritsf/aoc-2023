#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <numeric>

constexpr auto USE_SMALL_INPUT = false;
constexpr auto INPUT_PATH = USE_SMALL_INPUT ? "small_input.txt" : "input.txt";

// Function to parse numbers from a string and return them as a set.
std::set<int> parseNumbers(const std::string &numbers)
{
    std::stringstream numberStream(numbers);
    int number;
    auto numberSet = std::set<int>{};

    while (numberStream >> number)
    {
        numberSet.insert(number);
    }
    return numberSet;
}

int main()
{
    std::ifstream input(INPUT_PATH);

    // Check if the input file is open.
    if (!input.is_open())
    {
        std::cerr << "Could not open file " << INPUT_PATH << std::endl;
        return 1;
    }

    int totalPoints = 0;
    std::string line;

    // Process each line in the input file
    while (std::getline(input, line))
    {
        auto colonPos = line.find(':');
        auto verticalPos = line.find('|');

        auto winningNumbers = parseNumbers(line.substr(colonPos + 2, verticalPos - colonPos - 2));
        auto ourNumbers = parseNumbers(line.substr(verticalPos + 2));

        std::set<int> intersection;
        std::set_intersection(winningNumbers.begin(), winningNumbers.end(), ourNumbers.begin(), ourNumbers.end(), std::inserter(intersection, intersection.begin()));

        int intersectionSize = intersection.size();
        if (intersectionSize > 0)
        {
            // Calculate points based on the number of matching numbers.
            totalPoints += 1 << (intersectionSize - 1);
        }
    }

    std::cout << "Total points: " << totalPoints << std::endl;

    return 0;
}
