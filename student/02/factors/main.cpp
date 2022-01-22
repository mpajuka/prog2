#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int number;
    cin >> number;
    if (number <= 0 ) {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }

    int shortest_distance = number;
    int a = 1, b = 1;

    for(int i = 1; i < number; i++) {
        int n = number / i;
        if(i*n == number) {
            int distance = n - i;
            if(distance < 0) {
                distance = -distance;
            }
            if(distance < shortest_distance) {
                shortest_distance = distance;
                a = i;
                b = n;

            }
        }
    }

    cout << number << " = " << a << " * " << b << endl;
    return 0;
}
