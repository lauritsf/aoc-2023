#include <iostream>
#include <fstream>
#include <string>

constexpr char INPUT_FILENAME[] = "input";

int main()
{
    // Open the file
    // RAII: The file will be closed automatically when input_file goes out of scope
    std::ifstream input_file(INPUT_FILENAME);

    // Check if the file was opened, if not, print an error and return
    if (!input_file.is_open())
    {
        std::cerr << "Could not open file " << INPUT_FILENAME << std::endl;
        return 1;
    }

    // Initialize the total sum of all extracted numbers
    int total_sum = 0;
    std::string line;

    // Read the file line by line
    while (std::getline(input_file, line))
    {
        // Initialize the first and last digit of the number as null characters
        char first_digit = '\0';
        char last_digit = '\0';

        // Iterate over the line and find the first and last digit
        for (char c : line)
        {
            if (isdigit(c))
            {
                if (first_digit == '\0')
                {
                    first_digit = c;
                }
                last_digit = c;
            }
        }

        // If both digits were found, convert them to a number and add it to the total sum
        if (first_digit != '\0' && last_digit != '\0')
        {
            std::string digits{first_digit, last_digit};
            try
            {
                int number = std::stoi(digits);
                total_sum += number;
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid number found: " << digits << std::endl;
            }
        }
    }

    // Print the total sum
    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}
