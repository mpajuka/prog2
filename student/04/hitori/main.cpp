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
    //for (unsigned int i = 1; i < BOARD_SIDE; i++)
        //if ()
}

bool check_duplicate_numbers(vector<vector<int>>& gameboard)
{
    bool has_duplicate = false;
    // Check for duplicates horizontally,
    // by checking whether the next number of 'j'
    // has the same variable
    for (unsigned int i = 0; i < BOARD_SIDE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIDE; j++)
        {
            for (unsigned int n = j + 1; n < BOARD_SIDE; n++)
            {
                if (gameboard.at(i).at(j) != 0 and gameboard.at(i).at(j) == gameboard.at(i).at(n))
                {
                    has_duplicate = true;
                }
            }
        }
    }

    // Check for duplicates vertically in
    // the same principle as for the one above
    for (unsigned int i = 0; i < BOARD_SIDE; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIDE; j++)
        {
            for (unsigned int n = i + 1; n < BOARD_SIDE; n++)
            {
                if (gameboard.at(i).at(j) != 0 and gameboard.at(i).at(j) == gameboard.at(n).at(j))
                {
                    has_duplicate = true;
                }
            }
        }
    }

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

        for (int i = 0; i < 2; i++)
        {
            cin >> check_input;
            if (check_input == "q" or check_input == "Q")
            {
                cout << "Quitting" << endl;
                return gameboard;
            }

            int num = stoi_with_check(check_input);
            coordinates.push_back(num);
        }

        unsigned int x = coordinates.at(0);
        unsigned int y = coordinates.at(1);

        if (x < 1 or y < 1 or x > 5 or y > 5)
        {
            cout << "Out of board" << endl;
            continue;
        }
        if (gameboard.at(y-1).at(x-1) == 0)
        {
            cout << "Already removed" << endl;
            continue;
        }
        gameboard.at(y-1).at(x-1) = 0;
        print(gameboard);
        // check_surrounding_numbers(gameboard);

        check_duplicate_numbers(gameboard);

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
        cin >> choice;

        if (choice == "r" or choice == "R")
        {
            vector<vector<int>> gameboard;
            create_random_board(gameboard);
            print(gameboard);
            start_game(gameboard);
            break;
        }
        if (choice == "i" or choice == "I")
        {
            vector<vector<int>> gameboard;
            create_input_board(gameboard);
            print(gameboard);
            start_game(gameboard);
            break;
        }
    }
    return 0;
}
