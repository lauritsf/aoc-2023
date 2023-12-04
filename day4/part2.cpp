#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <numeric>
#include <unordered_map>

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

int getNumberOfCards(const std::unordered_map<int, int> &numbers)
{
    auto accumulator = [](int total, const auto &pair)
    {
        return total + pair.second;
    };
    return std::accumulate(numbers.begin(), numbers.end(), 0, accumulator);
}

struct ScratchCard
{
    int id;
    int winCount;
};

std::vector<ScratchCard> readScratchCards(std::istream &input)
{
    std::vector<ScratchCard> scratchCards;
    std::string line;
    while (std::getline(input, line))
    {
        auto colonPos = line.find(':');
        auto verticalPos = line.find('|');

        auto cardID = std::stoi(line.substr(5, colonPos));
        auto winningNumbers = parseNumbers(line.substr(colonPos + 2, verticalPos - colonPos - 2));
        auto ourNumbers = parseNumbers(line.substr(verticalPos + 2));

        std::set<int> intersection;
        std::set_intersection(winningNumbers.begin(), winningNumbers.end(), ourNumbers.begin(), ourNumbers.end(), std::inserter(intersection, intersection.begin()));

        int winCount = intersection.size();

        scratchCards.push_back(ScratchCard{cardID, winCount});
    }
    return scratchCards;
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

    auto scratchCards = readScratchCards(input);
    std::unordered_map<int, int> cardCounts;
    for (const auto &card : scratchCards)
    {
        cardCounts[card.id] = 1;
    }

    for (const auto &[id, winCount] : scratchCards)
    {
        for (int incrementID = id + 1; incrementID <= id + winCount; ++incrementID)
        {
            // Only add cards if they exist
            if (cardCounts[incrementID] > 0)
            {
                cardCounts[incrementID] += cardCounts[id];
            }
        }
    }

    std::cout << "Final Number of Scratchcards: " << getNumberOfCards(cardCounts) << std::endl;

    return 0;
}
