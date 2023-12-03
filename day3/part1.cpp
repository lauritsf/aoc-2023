#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <string>
#include <charconv>
#include <algorithm>

constexpr auto INPUT_PATH = "input.txt";

constexpr auto EMPTY_CHAR = '.';
using Coordinate = std::pair<int, int>;

struct PartNumber
{
    int number;
    std::vector<Coordinate> coordinates;
};

bool isSymbol(char c)
{
    return !isdigit(c) && c != EMPTY_CHAR;
}

template <typename T>
class Matrix
{
public:
    Matrix() : m_width(0), m_height(0) {}
    Matrix(size_t width, size_t height, const T &initialValue = T())
        : m_width(width), m_height(height), m_matrix(height, std::vector<T>(width, initialValue)) {}

    const T &get(size_t x, size_t y) const
    {
        return m_matrix.at(y).at(x);
    }

    void set(size_t x, size_t y, const T &value)
    {
        m_matrix.at(y).at(x) = value;
    }

    size_t getWidth() const
    {
        return m_width;
    }

    size_t getHeight() const
    {
        return m_height;
    }

private:
    size_t m_width;
    size_t m_height;
    std::vector<std::vector<T>> m_matrix;
};

class EngineSchematic
{
public:
    EngineSchematic(const Matrix<char> &schematic) : m_schematic(schematic) {}
    EngineSchematic(std::ifstream &schematic)
    {
        if (!schematic)
        {
            throw std::runtime_error("Failed to open schematic file");
        }

        auto parsedSchematic = parseSchematic(schematic);
        if (!parsedSchematic.has_value())
        {
            throw std::runtime_error("Failed to parse schematic");
        }
        m_schematic = parsedSchematic.value();
    }

    size_t getWidth() const
    {
        return m_schematic.getWidth();
    }

    size_t getHeight() const
    {
        return m_schematic.getHeight();
    }

    bool isAdjacentToSymbol(size_t x, size_t y) const
    {
        for (auto i = -1; i <= 1; ++i)
        {
            auto xCoord = x + i;
            if (xCoord < 0 || xCoord >= getWidth())
            {
                continue;
            }
            for (auto j = -1; j <= 1; ++j)
            {
                auto yCoord = y + j;
                if (yCoord < 0 || yCoord >= getHeight())
                {
                    continue;
                }
                if (isSymbol(m_schematic.get(xCoord, yCoord)))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isAdjacentToSymbol(PartNumber partNumber) const
    {
        for (auto [x, y] : partNumber.coordinates)
        {
            if (isAdjacentToSymbol(x, y))
            {
                return true;
            }
        }
        return false;
    }

    std::vector<PartNumber> getPartNumbers()
    {
        std::vector<PartNumber> partNumbers;
        for (auto y = 0; y < getHeight(); ++y)
        {
            std::string partNumberString;
            std::vector<Coordinate> partNumberCoordinates;
            for (auto x = 0; x < getWidth(); ++x)
            {
                auto c = m_schematic.get(x, y);
                if (isdigit(c)) // Part of a part number
                {
                    partNumberString += c;
                    partNumberCoordinates.emplace_back(x, y);
                    if (x == getWidth() - 1) // Last character of the line
                    {
                        int partNumber;
                        std::from_chars(partNumberString.data(), partNumberString.data() + partNumberString.size(), partNumber);
                        partNumbers.emplace_back(PartNumber{partNumber, partNumberCoordinates});
                        partNumberString.clear();
                        partNumberCoordinates.clear();
                    }
                }
                // Not a digit, partNumberString is not empty
                // -> We just finished reading a part number
                else if (!partNumberString.empty())
                {
                    int partNumber;
                    std::from_chars(partNumberString.data(), partNumberString.data() + partNumberString.size(), partNumber);
                    partNumbers.emplace_back(PartNumber{partNumber, partNumberCoordinates});
                    partNumberString.clear();
                    partNumberCoordinates.clear();
                }
            }
        }

        return partNumbers;
    }

private:
    Matrix<char> m_schematic;

    std::optional<Matrix<char>> parseSchematic(std::ifstream &schematic)
    {
        std::vector<std::string> schematicVector;
        std::string line;
        while (std::getline(schematic, line))
        {
            schematicVector.push_back(line);
        }

        if (schematicVector.empty())
        {
            std::cerr << "Schematic is empty" << std::endl;
            return std::nullopt;
        }

        size_t width = schematicVector.at(0).size();
        size_t height = schematicVector.size();
        for (auto line : schematicVector)
        {
            if (line.size() != width)
            {
                std::cerr << "Schematic is not rectangular" << std::endl;
                return std::nullopt;
            }
        }

        Matrix<char> schematicMatrix(width, height, EMPTY_CHAR);

        // Fill the matrix
        for (auto y = 0; y < height; ++y)
        {
            auto line = schematicVector.at(y);
            for (auto x = 0; x < width; ++x)
            {
                schematicMatrix.set(x, y, line.at(x));
            }
        }

        return schematicMatrix;
    }
};

int main()
{
    try
    {
        std::ifstream inputStream(INPUT_PATH);
        EngineSchematic schematic(inputStream);

        std::vector<PartNumber> partNumbers = schematic.getPartNumbers();
        int sum = 0;
        for (const auto &partNumber : partNumbers)
        {
            if (schematic.isAdjacentToSymbol(partNumber))
            {
                sum += partNumber.number;
            }
        }
        std::cout << "Sum of the part numbers adjacent to a symbol: " << sum << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
