#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string input_file;
    std::string output_file;

    std::cout << "Input file: ";
    getline(std::cin, input_file);

    std::cout << "Output file: ";
    getline(std::cin, output_file);

    std::ifstream file_object(input_file);
    std::ofstream output(output_file);

    if (not file_object)
    {
        std::cout << "Error! The file " << input_file << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        int row_count = 1;
        std::string line;
        while (getline(file_object, line))
        {
            output << row_count << " " << line << std::endl;
            row_count++;
        }
        file_object.close();
        output.close();
    }

    return 0;
}
