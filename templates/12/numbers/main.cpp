/* Numbers ( or 2048, but that's an invalid name ) : Model code
 *
 * Desc:
 *  This program generates a game of 2048, a tile combining game
 * where the goal is to get from 2's to 2048. The board is SIZE x SIZE,
 * (original was 4 x 4) and every round the player chooses a direction
 * to which the tiles should fall. If they collide with a wall or a different
 * value, they will move as close as they can get. If they collide with
 * a tile with same value, they will combine and double the value. The
 * tile will continue to move and combine until a wall or other tile comes along.
 * (This means there's some recursion, see NumberTile::move().
 *  Game will end when the GOAL (orig 2048) is reached or new tile can't be
 * added to the board.
 * */

#include "numbertile.hh"
#include "gameboard.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>

const Coords DEFAULT_DIR = {0, 0};
const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};

// Reads seed value given by the user and returns it for the caller.
int ask_for_seed()
{
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);

    if( seed == "" )
    {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        return time(NULL);
    }
    else
    {
        // If the user gave a seed value, use it.
        return stoi(seed);
    }
}

int ask_for_goal()
{
    std::cout << "Give a goal value or an empty line: ";
    std::string input = "";
    getline(std::cin, input);
    for( auto c : input )
    {
        if( std::isdigit(c) )
        {
            return std::stoi(input);
        }
    }
    return DEFAULT_GOAL;
}

int main()
{
    GameBoard board;
    int seed = ask_for_seed();
    board.init_empty();
    board.fill(seed);
    int goal = ask_for_goal();

    std::string input = "";
    bool print_flag = true;
    while( input != "q" )
    {
        if( print_flag )
        {
            board.print();
        }
        else
        {
            print_flag = true;
        }
        std::cout << "Dir> ";
        input.clear();
        std::getline(std::cin, input);
        if(input.size() == 0)
        {
            print_flag = false;
            continue;
        }
        Coords dir = DEFAULT_DIR;

        switch( input.at(0) )
        {
        case 'a': dir = LEFT; break;
        case 'w': dir = UP; break;
        case 'd': dir = RIGHT; break;
        case 's': dir = DOWN; break;
        case 'q': continue; break;
        default:
            std::cout << "Error: unknown command." << std::endl;
            print_flag = false;
            break;
        }

        if( dir != DEFAULT_DIR )
        {
            if( board.move(dir, goal) )
            {
                board.print();
                std::cout << "You reached the goal value of " << goal << "!" << std::endl;
                break;
            }
            else if( board.is_full() )
            {
                std::cout << "Can't add new tile, you lost!" << std::endl;
                break;
            }
            board.new_value(false);
        }
    }
    return 0;
}
