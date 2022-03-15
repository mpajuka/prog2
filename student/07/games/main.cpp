/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 * EXAMPLE SOLUTION
 * ===============================
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <ctype.h>
#include <set>

const std::string INPUT_PROMPT = "Give a name for input file: ",
                FILE_NOT_READ = "Error: File could not be read",
                FILE_WRONG_FORMAT = "Error: Invalid format in file";


using GAMES = std::map<std::string, std::map<std::string, int>>;

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}


bool line_correct(std::vector<std::string> const& parts)
{
   return parts.size() == 3
           and not parts.at(0).empty() and not parts.at(1).empty();
}

bool read_input(GAMES& data)
{
    std::string file_name;
    std::cout << INPUT_PROMPT;
    getline(std::cin, file_name);

    std::ifstream file(file_name);
    if (not file)
    {
        std::cout << FILE_NOT_READ << "\n";
        return false;
    }

    std::string line = "";
    std::vector<std::string> parts;
    while(std::getline(file, line))
    {
        parts = split(line);

        if (not line_correct(parts))
        {
            std::cout << FILE_WRONG_FORMAT << "\n";
            file.close();
            return false;
        }
        std::string game_name = parts.at(0),
                    player_name = parts.at(1),
                    points = parts.at(2);

        if (data.find(game_name) == data.end())
        {
            data.insert({game_name, {}});
        }
        data.at(game_name).insert({player_name, std::stoi(points)});
    }
    return true;
}


int main()
{
    GAMES data;
    if (not read_input(data))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
