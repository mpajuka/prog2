#include <iostream>
#include <fstream>
#include <string>
#include <map>

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
        std::map<std::string, int> players;
        std::string name;
        int points;

        std::cout << "Final scores:\n";
        while(getline(file, name))
        {
            std::string::size_type i = 0;
            i = name.find(':');
            points = stoi(name.substr(i + 1));
            name = name.substr(0, i);

            if (players.find(name) != players.end())
            {
                players[name] += points;
            }
            else
            {
                players.insert({name, points});
            }
        }

        file.close();
        for (auto & participants : players)
        {
            std::cout << participants.first
                      << ": "
                      << participants.second
                      << std::endl;
        }

    }
}
