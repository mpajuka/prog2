#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int numbers = 0;
    std::cin >> numbers;

    for ( int counter = 1; counter < numbers + 1; ++counter )
        std::cout << counter << std::endl;

    return 0;
}
