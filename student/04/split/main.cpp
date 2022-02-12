#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(const std::string& line, const char separator, bool no_separator=false)
{
    std::vector<std::string> full_text;
    std::string consecutive_chars;

    for (const char i : line)
    {
        if (i == separator)
        {
            if (consecutive_chars.empty() and no_separator)
            {
                continue;
            }
            full_text.push_back(consecutive_chars);
            consecutive_chars = "";
        }
        else
        {
            consecutive_chars += i;
        }
    }
    full_text.push_back(consecutive_chars);
    return full_text;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
