#include "Matrix.h"
#include <iostream>
#include <exception>

Matrix::Matrix()
{
    m = 0;
    n = 0;
    arr = NULL;
}

Matrix::Matrix(size_t m, size_t n)
{
    this->m = m;
    this->n = n;
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

    //Initialize array to zeroes
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            arr[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    for (unsigned int i = 0; i < m; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}