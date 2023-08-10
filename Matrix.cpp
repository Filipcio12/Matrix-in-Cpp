#include "Matrix.h"
#include <cstdlib>
#include <iostream>

Matrix::Matrix()
{
    arr = NULL;
}

Matrix::Matrix(unsigned int m, unsigned int n)
{
    arr = new double*[m];
    if (!arr) {
        fprintf(stderr, "Error");
        abort();
    }
    for (unsigned int i = 0; i < m; ++i) {
        arr[i] = new double[n];
        if (!arr[i]) {
            fprintf(stderr, "Error");
        }
    }
}