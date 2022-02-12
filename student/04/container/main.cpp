#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{    
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values(std::vector<int> integers)
{
    int first_number = integers.at(0);
    for (int number : integers)
    {
        if (number != first_number)
        {
             return false;
        }
    }
    return true;
}

bool is_ordered_non_strict_ascending(std::vector<int> integers)
{
    int previous_number = integers.at(0);
    for (int new_number : integers)
    {
        if (new_number < previous_number)
        {
            return false;
        }
        previous_number = new_number;
    }
    return true;
}

bool is_arithmetic_series(std::vector<int> integers)
{
    int difference = integers.at(1) - integers.at(0);
    int previous_number = integers.at(0);

    for (int number : integers)
    {
        if (number != previous_number and number - previous_number != difference)
        {
            return false;
        }
        previous_number = number;
    }
    return true;
}

bool is_geometric_series(std::vector<int> integers)
{
    if (integers.at(0) == 0 and same_values(integers))
    {
        return false;
    }

    int difference = integers.at(1) / integers.at(0);
    int previous_number = integers.at(0);

    for (int number : integers)
    {
        if (number != previous_number and number / previous_number != difference)
        {
            return false;
        }
        previous_number = number;
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return 0;
}
