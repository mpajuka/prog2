#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int numbers = 0;
    std::cin >> numbers;

    for ( int counter = 1; counter < numbers + 1; ++counter )
        if ( counter % 3 == 0 && counter % 7 == 0) {
            std::cout << "zip boing" << std::endl;
        } else if ( counter % 7 == 0) {
            std::cout << "boing" << std::endl;
        } else if ( counter % 3 == 0) {
            std::cout << "zip" << std::endl;
        } else {
            std::cout << counter << std::endl;
        }
    return 0;
}
