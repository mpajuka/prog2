#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int number;
    cin >> number;
    if (number <= 0 ) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        cout << number % 2 << endl;
    }
    return 0;
}
