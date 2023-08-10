#include "Matrix.h"
#include <iostream>

int main()
{
    Matrix a(2, 2);
    Matrix& b = a;
    std::cout << a << b;
    return 0;
}