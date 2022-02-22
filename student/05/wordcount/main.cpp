#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>

int main()
{
    std::string input_file;

    std::cout << "Input file: ";
    getline(std::cin, input_file);

    std::ifstream file(input_file);


    if (not file)
    {
        std::cout << "Error! The file " << input_file << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::map<std::string, std::set<int>> row_info;
        std::string word;
        std::string row;
        int row_count = 1;

        while (getline(file, row))
        {
            std::istringstream words(row);
            while (words >> word)
            {
                if (row_info.find(word) == row_info.end())
                {
                    row_info.insert({word, {}});
                }
                row_info[word].insert(row_count);
            }
            row_count++;
        }

        for (std::map<std::string, std::set<int>>::const_iterator
             iter = row_info.begin(); iter != row_info.end(); iter++)
        {
            std::string key = iter->first;
            std::set<int> row_numbers = iter->second;
            std::cout << key << " " << row_numbers.size() << ": ";
            for (std::set<int>::iterator iter = row_numbers.begin();
                 iter != row_numbers.end(); iter++)
            {
                std::cout << *iter;
                if ((++iter) != row_numbers.end())
                {
                    std::cout << ", ";
                }
                else {
                    std::cout << "\n";
                }
                iter--;
            }
        }
    }
    file.close();
}
