#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter a number:" << endl;
    cin >> n;

    int cube = n * n * n;
    if ( cube/n/n != n) {
        cout << "Error! the cube of " << n << " is not " << cube << endl;
    } else {
        cout << "The cube of " << n << " is " << cube << endl;
    }

    return 0;
}
