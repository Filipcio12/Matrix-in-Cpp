#include "Matrix.h"
#include <iostream>

int main()
{
    Matrix a(2, 2);
    Matrix b(3, 3);
    b = a;
    std::cout << a << b;
    return 0;
}