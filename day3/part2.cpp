#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <string>
#include <charconv>
#include <algorithm>
#include <functional>

constexpr char INPUT_PATH[] = "input.txt";
constexpr char EMPTY_CHAR = '.';
constexpr char GEAR_CHAR = '*';

using Coordinate = std::pair<int, int>;
struct CoordinateHash
{
    size_t operator()(const Coordinate &c) const
    {
        return std::hash<int>()(c.first) ^ (std::hash<int>()(c.second) << 1);
    }
};

struct Symbol
{
    char value;
    Coordinate coordinate;
};

bool isSymbol(char c)
{
    return !isdigit(c) && c != EMPTY_CHAR;
}

struct PartNumber
{
    int number;
    std::vector<Coordinate> coordinates;
    std::vector<Symbol> adjacentSymbols;
};

struct Gear : public Symbol
{
    int gearRatio;

    Gear(char value, Coordinate coordinate, int gearRatio)
        : Symbol{value, coordinate}, gearRatio(gearRatio) {}
};

std::vector<std::string> readSchematic(std::istream &input)
{
    std::vector<std::string> schematic;
    std::string line;
    while (std::getline(input, line))
    {
        schematic.push_back(line);
    }
    return schematic;
}

std::vector<Symbol> getAdjacentSymbols(const std::vector<std::string> &schematic, const std::vector<Coordinate> &coordinates)
{
    std::vector<Symbol> adjacentSymbols;
    std::vector<Coordinate> adjacentCoordinates;

    auto max_x = schematic.at(0).size();
    auto max_y = schematic.size();

    static const int dx[]{-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dy[]{-1, 0, 1, -1, 1, -1, 0, 1};

    for (const auto &[x, y] : coordinates)
    {
        for (int i = 0; i < 8; ++i)
        {
            auto adj_x = x + dx[i];
            auto adj_y = y + dy[i];
            if (adj_x >= 0 && adj_x < max_x && adj_y >= 0 && adj_y < max_y)
            {
                adjacentCoordinates.push_back({adj_x, adj_y});
            }
        }
    }

    // Remove duplicates
    std::sort(adjacentCoordinates.begin(), adjacentCoordinates.end());
    adjacentCoordinates.erase(std::unique(adjacentCoordinates.begin(), adjacentCoordinates.end()), adjacentCoordinates.end());

    // Get symbols
    for (const auto &[x, y] : adjacentCoordinates)
    {
        auto c = schematic.at(y).at(x);
        if (isSymbol(c))
        {
            adjacentSymbols.push_back({c, {x, y}});
        }
    }

    return adjacentSymbols;
}

std::vector<PartNumber> getPartNumbers(const std::vector<std::string> &schematic)
{
    std::vector<PartNumber> partNumbers;
    std::string numberStr;
    std::vector<Coordinate> numberCoordinates;
    bool finishedReadingNumber = false;
    for (int y = 0; y < schematic.size(); ++y)
    {
        for (int x = 0; x < schematic.at(y).size(); ++x)
        {
            auto c = schematic.at(y).at(x);
            if (isdigit(c))
            {
                numberStr += c;
                numberCoordinates.push_back({x, y});
            }
            else if (!numberStr.empty())
            {
                finishedReadingNumber = true;
            }
            auto isEndOfLine = x == schematic.at(y).size() - 1;
            if (isEndOfLine && !numberStr.empty())
            {
                finishedReadingNumber = true;
            }
            if (finishedReadingNumber)
            {

                auto adjacentSymbols = getAdjacentSymbols(schematic, numberCoordinates);
                // Only add numbers that have adjacent symbols
                if (!adjacentSymbols.empty())
                {
                    partNumbers.push_back(
                        PartNumber{
                            std::stoi(numberStr),
                            numberCoordinates,
                            adjacentSymbols});
                }
                numberStr.clear();
                numberCoordinates.clear();
                finishedReadingNumber = false;
            }
        }
    }
    return partNumbers;
}

std::vector<Gear> getGears(const std::vector<PartNumber> &partNumbers)
{
    std::unordered_map<Coordinate, std::vector<int>, CoordinateHash> gearMap;
    for (const auto &partNumber : partNumbers)
    {
        for (const auto &symbol : partNumber.adjacentSymbols)
        {
            if (symbol.value == GEAR_CHAR)
            {
                gearMap[symbol.coordinate].push_back(partNumber.number);
            }
        }
    }

    std::vector<Gear> gearVector;
    // Loop over gearMap and create Gear objects
    for (const auto &[coordinate, numberVector] : gearMap)
    {
        if (numberVector.size() == 2)
        {
            // product of two numbers
            auto gearRatio = numberVector.at(0) * numberVector.at(1);
            gearVector.emplace_back(Gear{GEAR_CHAR, coordinate, gearRatio});
        }
    }
    return gearVector;
}

int main()
{
    std::ifstream input(INPUT_PATH);
    auto schematic = readSchematic(input);
    auto partNumbers = getPartNumbers(schematic);
    auto gears = getGears(partNumbers);

    auto gearRatioSums = 0;
    for (const auto &gear : gears)
    {
        gearRatioSums += gear.gearRatio;
    }
    std::cout << "Sum of gear ratios: " << gearRatioSums << std::endl;
}
