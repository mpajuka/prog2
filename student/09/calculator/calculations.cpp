// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exponent(double left, double right)
{
    double result = 1;
    for (double i = 0; i < right; i += 1.0)
    {
        result *= left;
    }
    return result;
}
