/*  Hitori
 *  --------------------
 *  Kuvaus:
 *  --------------------
 *  Ohjelman kirjoittaja
 *  --------------------
 *  Nimi: Miska Pajukangas
 *  Opiskelijanumero: 150281685
 *  Käyttäjätunnus: bxmipa
 *  E-Mail: miska.pajukangas@tuni.fi
 */

#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const /*vector of vectors or a compatible type*/vector<vector<int>>& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

bool check_surrounding_numbers(vector<vector<int>>& gameboard)
{
    // Checks if the player has deleted a number adjacent
    // to an already deleted one
    for (unsigned int i = 0; i < BOARD_SIDE - 1; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIDE - 1; j++)
        {
            if (gameboard.at(i).at(j) == 0)
            {
                if (gameboard.at(i + 1).at(j) == 0
                        or gameboard.at(i).at(j + 1) == 0)
                {
                    return true;
                }
            }

        }
    }
    for (unsigned int i = 1; i < BOARD_SIDE; i++)
    {
        for (unsigned int j = 1; j < BOARD_SIDE; j++)
        {
            if (gameboard.at(i).at(j) == 0)
            {
                if (gameboard.at(i - 1).at(j) == 0
                        or gameboard.at(i).at(j - 1) == 0)
                {
                    return true;
                }
            }
        }
    }

    // Structure for checking every side and center of the board
    // with the same principle as previously
    for (unsigned int i = 1; i < BOARD_SIDE - 1; i++)
    {
        for (unsigned int j = 1; j < BOARD_SIDE - 1; j++)
        {
            // Check sides
            if (gameboard.at(0).at(i) != 0)
            {
                if (gameboard.at(0).at(i - 1) == 0
                    and gameboard.at(0).at(i + 1) == 0
                    and gameboard.at(1).at(i) == 0)
                {
                    return true;
                }
                if (gameboard.at(4).at(i - 1) == 0
                    and gameboard.at(4).at(i + 1) == 0
                    and gameboard.at(3).at(i) == 0)
                {
                    return true;
                }
            }
            if (gameboard.at(i).at(0) != 0)
            {
                if (gameboard.at(i - 1).at(0) == 0
                    and gameboard.at(i + 1).at(0) == 0
                    and gameboard.at(i).at(1) == 0)
                {
                    return true;
                }
                if (gameboard.at(i - 1).at(4) == 0
                    and gameboard.at(i + 1).at(4) == 0
                    and gameboard.at(i).at(3) == 0)
                {
                    return true;
                }
            }
            if (gameboard.at(i).at(4) != 0)
            {
                if (gameboard.at(i - 1).at(4) == 0
                    and gameboard.at(i + 1).at(4) == 0
                    and gameboard.at(i).at(3) == 0)
                {
                    return true;
                }
            }
            // Check center
            if (gameboard.at(i).at(j) != 0)
            {
                if (gameboard.at(i - 1).at(j) == 0
                    and gameboard.at(i).at(j - 1) == 0
                    and gameboard.at(i + 1).at(j) == 0
                    and gameboard.at(i).at(j + 1) == 0)
                {
                    return true;
                }
            }
        }
    }

    // Checks every corner of the board, for not having any
    // adjacent vertical or horizontal variable
    if ((gameboard.at(0).at(0) != 0
         and gameboard.at(0).at(1) == 0 and gameboard.at(1).at(0) == 0)

        or (gameboard.at(4).at(0) != 0
            and gameboard.at(3).at(0) == 0 and gameboard.at(4).at(1) == 0)

        or (gameboard.at(0).at(4) != 0
            and gameboard.at(0).at(3) == 0 and gameboard.at(1).at(4) == 0)

        or (gameboard.at(4).at(4) != 0
            and gameboard.at(3).at(4) == 0 and gameboard.at(4).at(3) == 0))
    {
        return true;
    }

    return false;
}

bool check_duplicate_numbers(vector<vector<int>>& gameboard)
{
    bool has_duplicate = false;
    // Check for duplicates horizontally in each row,
    // by checking whether the next number of 'j'
    // has the same variable as 'n'
    for (unsigned int i = 0; i < BOARD_SIDE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIDE; j++)
        {
            for (unsigned int n = j + 1; n < BOARD_SIDE; n++)
            {
                if (gameboard.at(i).at(j) != 0
                        and gameboard.at(i).at(j) == gameboard.at(i).at(n))
                {
                    has_duplicate = true;
                }
            }
        }
    }
    // Check for duplicates vertically in each column
    // with the same principle as for the one above
    for (unsigned int i = 0; i < BOARD_SIDE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIDE; j++)
        {
            for (unsigned int n = i + 1; n < BOARD_SIDE; n++)
            {
                if (gameboard.at(i).at(j) != 0
                        and gameboard.at(i).at(j) == gameboard.at(n).at(j))
                {
                    has_duplicate = true;
                }
            }
        }
    }

    // Returns a value after all variables have been
    // checked, and a result depending on that
    if (has_duplicate == true)
    {
        return true;
    }
    return false;
}

vector<vector<int>> start_game(vector<vector<int>>& gameboard)
{
    while (true)
    {
        string check_input;
        cout << "Enter removable element (x, y): ";
        vector<int> coordinates;

        // Reads two inputs from the user
        for (int i = 0; i < 2; i++)
        {
            cin >> check_input;
            if (check_input == "q" or check_input == "Q")
            {
                cout << "Quitting" << endl;
                return gameboard;
            }
            // Checks whether the user input
            // contains an integer, returns 0 if not
            int num = stoi_with_check(check_input);
            coordinates.push_back(num);
        }

        unsigned int x = coordinates.at(0);
        unsigned int y = coordinates.at(1);

        // Starts the loop again if the coordinates
        // are not between 1 and 5
        if (x < 1 or y < 1 or x > 5 or y > 5)
        {
            cout << "Out of board" << endl;
            continue;
        }
        // If the gameboard has already been removed
        // at the given location
        if (gameboard.at(y-1).at(x-1) == 0)
        {
            cout << "Already removed" << endl;
            continue;
        }
        gameboard.at(y-1).at(x-1) = 0;
        print(gameboard);

        // Calls the function to check if the user
        // has falsely removed numbers from the board
        // resulting in a lose scenario
        if (check_surrounding_numbers(gameboard))
        {
            cout << "You lost" << endl;
            return gameboard;
        }

        // Calls the function to check whether
        // each row and column contains any vertical
        // or horizontal duplicates
        if (not check_duplicate_numbers(gameboard))
        {
            cout << "You won" << endl;
            return gameboard;
        }
    }
    return gameboard;
}

vector<vector<int>> create_random_board(vector<vector<int>>& gameboard)
{
    int seed = 0;
    cout << "Enter seed value: ";
    cin >> seed;
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(1, 5);

    // Adds randomly generated integers to the game board
    for (unsigned int i = 0; i < BOARD_SIDE; i++)
    {
        vector<int> v1;
        for (unsigned int j = 0; j < BOARD_SIDE; j++)
        {
            v1.push_back(distr(gen));
        }
        gameboard.push_back(v1);
    }
    return gameboard;
}

vector<vector<int>> create_input_board(vector<vector<int>>& gameboard)
{
    cout << "Input: ";
    vector<int> input_numbers;
    int new_int = 0;

    for (int i = 0; i < 25; i++)
    {
        cin >> new_int;
        input_numbers.push_back(new_int);
    }

    int int_count = 0;

    for (unsigned int i = 0; i < BOARD_SIDE; i++) {
        vector<int> v1;
        for (unsigned int j = 0; j < BOARD_SIDE; j++) {
            v1.push_back(input_numbers[int_count]);
            int_count++;
        }
        gameboard.push_back(v1);
    }
    return gameboard;
}


int main()
{
    string choice = "";
    while (true)
    {

        cout << "Select start (R for random, I for input): ";
        getline(cin, choice);
        vector<vector<int>> gameboard;

        // Selects seed generated game
        if (choice == "r" or choice == "R")
        {
            create_random_board(gameboard);
            print(gameboard);
            start_game(gameboard);
            break;
        }

        // Selects user-input based game
        if (choice == "i" or choice == "I")
        {

            create_input_board(gameboard);
            print(gameboard);
            start_game(gameboard);
            break;
        }
    }
    return 0;
}
