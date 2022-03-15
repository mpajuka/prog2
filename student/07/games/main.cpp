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
                FILE_WRONG_FORMAT = "Error: Invalid format in file.",
                ALL_GAMES_TEXT = "All games in alphabetical order:",
                WRONG_INPUT = "Error: Invalid input.",
                GAME_NOT_FOUND = "Error: Game could not be found.",
                ALL_PLAYERS_TEXT = "All players in alphabetical order.",
                PLAYER_NOT_FOUND = "Error: Player could not be found.";


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

// ALL_GAMES
void print_games(GAMES const& data)
{
    std::cout << ALL_GAMES_TEXT << "\n";

    for (auto entry : data)
    {
        std::cout << entry.first << "\n";
    }
}

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
        for (auto entry : data)
        {
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

        for (std::map<int, std::set<std::string>>::const_iterator
             it = scores.begin(); it != scores.end(); it++)
        {
            std::cout << it->first << " : ";
            std::set<std::string> player_names = it->second;
            for (std::set<std::string>::iterator it = player_names.begin();
                 it != player_names.end(); it++)
            {
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

void all_player_info(GAMES const& data)
{
    std::cout << ALL_PLAYERS_TEXT << "\n";
    std::set<std::string> name_list;

    for (auto entry : data)
    {
        std::map<std::string, int>& inner_map = entry.second;

        for (auto entry2 : inner_map)
        {
            if (name_list.find(entry2.first) == name_list.end())
            {
                name_list.insert(entry2.first);
            }
        }
    }
    for (auto it = name_list.begin(); it != name_list.end(); it++)
    {
        std::cout << *it << "\n";
    }
}

void single_player_info(GAMES const& data, std::string name)
{
    std::set<std::string> game_list;

    for (auto it : data)
    {
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

        for (auto game : game_list)
        {
            std::cout << game << "\n";
        }
    }

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
