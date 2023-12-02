#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

constexpr char INPUT_FILENAME[] = "input";

struct ColorCount
{
    int red = 0;
    int green = 0;
    int blue = 0;
};

class GameResult
{
public:
    int gameID;
    std::vector<ColorCount> colorCounts;

    GameResult(const int gameID, const std::vector<ColorCount> &colorCounts) : gameID(gameID), colorCounts(colorCounts) {}
    GameResult(const std::string &gameData) { parseGameData(gameData); }

    // Returns true if the game result is valid, false otherwise
    bool isValid(const ColorCount &cubesPerColor) const
    {
        for (const auto &[red, green, blue] : colorCounts)
        {
            if (red > cubesPerColor.red || green > cubesPerColor.green || blue > cubesPerColor.blue)
            {
                return false;
            }
        }
        return true;
    }

    // Returns the minimum number of cubes needed for this game result to be valid
    ColorCount cubesNeeded() const
    {
        ColorCount cubesNeeded;
        for (const auto &[red, green, blue] : colorCounts)
        {
            cubesNeeded.red = std::max(cubesNeeded.red, red);
            cubesNeeded.green = std::max(cubesNeeded.green, green);
            cubesNeeded.blue = std::max(cubesNeeded.blue, blue);
        }
        return cubesNeeded;
    }

private:
    void parseGameData(const std::string &data)
    {
        std::istringstream dataStream(data);
        std::string gameIdStr;
        std::getline(dataStream, gameIdStr, ':');
        gameID = std::stoi(gameIdStr.substr(gameIdStr.find("Game") + 5));

        std::string segment;
        while (std::getline(dataStream, segment, ';'))
        {
            ColorCount colorCount;
            std::istringstream segmentStream(segment);
            std::string color;
            int count;

            while (segmentStream >> count >> color)
            {
                switch (color[0])
                {
                case 'r':
                    colorCount.red = count;
                    break;
                case 'g':
                    colorCount.green = count;
                    break;
                case 'b':
                    colorCount.blue = count;
                    break;
                }
            }
            colorCounts.push_back(colorCount);
        }
    }
};

int main()
{
    std::ifstream inputFile(INPUT_FILENAME);

    std::vector<GameResult> gameResults;

    std::string line;
    while (std::getline(inputFile, line))
    {
        gameResults.push_back(GameResult(line));
    }

    int sumOfPowers = 0;

    for (const auto &gameResult : gameResults)
    {
        const auto cubesNeeded = gameResult.cubesNeeded();
        const auto cubesNeededProduct = cubesNeeded.red * cubesNeeded.green * cubesNeeded.blue;
        sumOfPowers += cubesNeededProduct;
    }

    std::cout << "Sum of powers: " << sumOfPowers << std::endl;
}
