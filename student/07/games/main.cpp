/*  COMP.CS.100 Project 2: GAME STATISTICS
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
 * Program author
 * ===============================
 * Name: Miska Pajukanags
 * Student number: 150281685
 * UserID: bxmipa
 * E-Mail: miska.pajukangas@tuni.fi
 *
 * A program which reads a .txt file in a way as a program would read
 * a .csv file. Splits the three parts of each line by a delimiter ";"
 * by 'game', 'player' and 'score'. After the file is read and inserted to the
 * data structure, the user can then fetch certain information about the data
 * using certain commands which for example print out all the games or
 * information about the scores of a game. The commands simply iterate or
 * insert the data to a data structure which is then printed out for the user
 * to see
 * */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <ctype.h>
#include <set>

// Prints for the user interface
const std::string INPUT_PROMPT = "Give a name for input file: ",
                FILE_NOT_READ = "Error: File could not be read",
                FILE_WRONG_FORMAT = "Error: Invalid format in file.",
                ALL_GAMES_TEXT = "All games in alphabetical order:",
                WRONG_INPUT = "Error: Invalid input.",
                GAME_NOT_FOUND = "Error: Game could not be found.",
                ALL_PLAYERS_TEXT = "All players in alphabetical order:",
                PLAYER_NOT_FOUND = "Error: Player could not be found.";

// The main data structure where values are stored from the text file
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

/**
 * Prints the names of the games, the "outer" part of the two maps,
 * or better referred as the keys of the map GAMES
 *
 * @brief print_games
 * @param data, the main data structure declared above with the name GAMES
 */
void print_games(GAMES const& data)
{
    std::cout << ALL_GAMES_TEXT << "\n";

    for (auto entry : data)
    {
        // Game names
        std::cout << entry.first << "\n";
    }
}

/**
 * Reads data from GAMES data structure and inserts correct info to scores
 *
 * Inserts information about each games player and their scores, inserts
 * the information to a new map which is read later by iterating through it
 *
 * @brief game_info
 * @param data, the main data structure declared above with the name GAMES
 * @param value, a user inputted string
 */
void game_info(GAMES const& data, std::string value)
{
    if (data.find(value) == data.end())
    {
        std::cout << GAME_NOT_FOUND << "\n";
    }

    else {
        std::cout << "Game "
                << value
                << " has these scores and players, listed in ascending order:"
                << "\n";

        std::map<int, std::set<std::string>> scores;
        // "Outer" part of the data structure, or the key as a string
        for (auto entry : data)
        {
            // Inner part of the loop, as to iterate through the map inside the
            // previous
            std::map<std::string, int>& second_map = entry.second;

            if (entry.first == value)
            {
                for (auto entry2 : second_map)
                {
                    if (scores.find(entry2.second) == scores.end())
                    {
                        scores.insert({entry2.second, {}});
                    }
                    scores[entry2.second].insert(entry2.first);
                }
            }
        }
        // Iterates through the map and splits the score number and players
        for (std::map<int, std::set<std::string>>::const_iterator
             it = scores.begin(); it != scores.end(); it++)
        {
            std::cout << it->first << " : ";
            std::set<std::string> player_names = it->second;
            for (std::set<std::string>::iterator it = player_names.begin();
                 it != player_names.end(); it++)
            {
                // iterates through the set inside the map, splits the strings
                // if the set contains more than one, else it moves to another
                // line
                std::cout << *it;
                if ((++it) != player_names.end())
                {
                    std::cout << ", ";
                }
                else {
                    std::cout << "\n";
                }
                it--;
            }
        }
    }
}

/**
 * Reads data with a for loop then places unique names in a set,
 * and prints the contents by iterating through
 *
 * @brief all_player_info
 * @param data, the main data structure declared above with the name GAMES
 */
void all_player_info(GAMES const& data)
{
    std::cout << ALL_PLAYERS_TEXT << "\n";
    std::set<std::string> name_list;

    // "Outer" part of the data structure, or the key as a string
    for (auto entry : data)
    {
        // Inner part of the loop, as to iterate through the map inside the
        // previous
        std::map<std::string, int>& inner_map = entry.second;
        for (auto entry2 : inner_map)
        {
            if (name_list.find(entry2.first) == name_list.end())
            {
                name_list.insert(entry2.first);
            }
        }
    }
    // Read and print out the set
    for (auto it = name_list.begin(); it != name_list.end(); it++)
    {
        std::cout << *it << "\n";
    }
}

/**
 * Reads through the data structure and adds a game to the set,
 * if the key has the same name as the users input. Later goes
 * through the set and prints out the contents
 *
 * @brief single_player_info
 * @param data, the main data structure declared above with the name GAMES
 * @param name, the user inputted string containing the name of the player
 */
void single_player_info(GAMES const& data, std::string name)
{
    std::set<std::string> game_list;

    // Reads the outer part of the data struct
    for (auto it : data)
    {
        // Inner part of the loop, as to iterate through the map inside the
        // previous
        std::map<std::string, int>& inner_map = it.second;
        for (auto it2 : inner_map)
        {
            if (it2.first == name and game_list.find(it.first) == game_list.end())
            {
                game_list.insert(it.first);
            }
        }
    }

    if (game_list.empty())
    {
        std::cout << PLAYER_NOT_FOUND << "\n";
    }
    else
    {
        std::cout << "Player "
                  << name
                  << " playes the following games:"
                  << "\n";

        // Read and print out the set
        for (auto game : game_list)
        {
            std::cout << game << "\n";
        }
    }

}

/**
 * Reads the vector with splitted parts, more so checks if the data line
 * has invalid parts or empty ones
 *
 *
 * @brief line_correct
 * @param parts, string splitted to game, player and score
 * @return
 */
bool line_correct(std::vector<std::string> const& parts)
{
   return parts.size() == 3
           and not parts.at(0).empty() and not parts.at(1).empty();
}

/**
 * Read the data file, line by line and insert the contents into data structure
 *
 * @brief read_input
 * @param data, the main data structure declared above with the name GAMES
 * @return
 */
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

/**
 * Main function which reads the commands and then moves to
 * the corresponding function
 *
 * @brief main
 * @return
 */
int main()
{
    GAMES data;
    if (not read_input(data))
    {
        return EXIT_FAILURE;
    }
    std::string user_input = "";
    std::vector<std::string> parts;

    while (true)
    {
        std::cout << "games> ";
        std::getline(std::cin, user_input);
        if (user_input == "")
        {
            continue;
        }
        parts = split(user_input, ' ');
        user_input = parts.at(0);


        // Converts string to uppercase by going through each character
        for (auto & c : user_input)
        {
            c = std::toupper(c);
        }

        if (user_input == "QUIT")
        {
            break;
        }
        else if (user_input == "ALL_GAMES")
        {
            print_games(data);
        }
        else if (user_input == "GAME")
        {
            if (parts.size() >= 2)
            {
                std::string value = parts.at(1);
                game_info(data, value);
            }
            else {
                std::cout << WRONG_INPUT << "\n";
            }
        }
        else if (user_input == "ALL_PLAYERS")
        {
            all_player_info(data);
        }
        else if (user_input == "PLAYER")
        {
            if (parts.size() == 2)
            {
                std::string name = parts.at(1);
                single_player_info(data, name);
            }
            else {
                std::cout << PLAYER_NOT_FOUND << "\n";
            }

        }
        else {
            std::cout << WRONG_INPUT << "\n";
        }
    }
    return EXIT_SUCCESS;
}
