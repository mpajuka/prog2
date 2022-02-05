#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
    cout << "Enter a seed value: ";
    int seed;
    cin >> seed;
    default_random_engine gen(seed);
    uniform_int_distribution<int> number(lower, upper);

    int i = 0;
    while (i == 0) {
        cout << endl << "Your drawn random number is " << number(gen)
             << endl;
        cout << "Press q to quit or any other key to continue: ";
        string answer;
        cin >> answer;
        if (answer == "q") {
            break;
        } else {
            continue;
        }
    }

}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
