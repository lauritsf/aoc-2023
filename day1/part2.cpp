#include <iostream>
#include <fstream>
#include <string>
#include <map>

constexpr char INPUT_FILENAME[] = "input";
const std::map<std::string, int> DIGIT_MAP = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

std::string convertWordToDigit(const std::string &word)
{
    auto it = DIGIT_MAP.find(word);
    if (it != DIGIT_MAP.end())
    {
        return std::to_string(it->second);
    }
    else
    {
        std::cerr << "Could not find digit for word " << word << std::endl;
        return "";
    }
}

int main()
{
    std::ifstream input_file(INPUT_FILENAME);
    if (!input_file.is_open())
    {
        std::cerr << "Could not open file " << INPUT_FILENAME << std::endl;
        return 1;
    }

    int total_sum = 0;
    std::string line;

    while (std::getline(input_file, line))
    {
        std::string first_digit;
        std::string last_digit;

        for (size_t i = 0; i < line.length(); ++i)
        {
            if (isdigit(line[i]))
            {
                if (first_digit.empty())
                    first_digit = line[i];
                last_digit = line[i];
            }
            else
            {
                // Find the longest matching word in DIGIT_MAP
                for (const auto &[word, value] : DIGIT_MAP)
                {
                    if (line.substr(i, word.length()) == word)
                    {
                        if (first_digit.empty())
                            first_digit = convertWordToDigit(word);
                        last_digit = convertWordToDigit(word);
                        break;
                    }
                }
            }
        }

        if (!first_digit.empty() && !last_digit.empty())
        {
            std::string digits = first_digit + last_digit;
            try
            {
                total_sum += std::stoi(digits);
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "Invalid number found: " << digits << std::endl;
            }
        }
    }

    std::cout << "Total sum: " << total_sum << std::endl;
    return 0;
}
