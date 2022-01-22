#include <iostream>

using namespace std;

unsigned long int factorial(int n) {
    unsigned long int factorial_value = 1;
    for(int i = 1; i <= n; ++i) {
        factorial_value *= i;
    }
    return factorial_value;
}

int lottery_game(int lotteryball_amount, int drawnball_amount) {
    unsigned long int answer;
    answer = factorial(lotteryball_amount) /
            (factorial(lotteryball_amount - drawnball_amount) * factorial(drawnball_amount));
    return answer;
}


int main()
{
    cout << "Enter the total number of lottery balls: ";
    int lotteryball_amount;
    cin >> lotteryball_amount;

    cout << "Enter the number of drawn balls: ";
    int drawnball_amount;
    cin >> drawnball_amount;
    if (lotteryball_amount < 0 or drawnball_amount < 0) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    } else if (drawnball_amount > lotteryball_amount) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    } else {
        cout << "The probability of guessing all " << drawnball_amount << " is "
             << "1/" << lottery_game(lotteryball_amount, drawnball_amount) << endl;
    }
    return 0;
}
