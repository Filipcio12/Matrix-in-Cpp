#pragma once
#include <cstdlib>

class Matrix {
    double** arr;
    size_t m;
    size_t n;

    public:
        Matrix();
        Matrix(size_t m, size_t n);
        ~Matrix();
        double operator()(size_t m, size_t n) const; // read only
        double& operator()(size_t m, size_t n); // write
};