#include "Matrix.h"
#include <iostream>

int main()
{
    Matrix a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;
    std::cout << a(0, 0);
    return 0;
}