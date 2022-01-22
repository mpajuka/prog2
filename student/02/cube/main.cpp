#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int n;
    cin >> n;



    int cube = n * n * n;
    if ( cube/n/n != n) {
        cout << "Error! the cube of " << n << " is not " << cube << endl;
    } else {
        cout << "The cube of " << n << " is " << cube << endl;
    }

    return 0;
}
