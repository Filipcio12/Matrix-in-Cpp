#pragma once
#include <cstdlib>
#include <iostream>

class Matrix {
    double** arr;
    size_t m;
    size_t n;

    public:   
        Matrix();
        Matrix(size_t m, size_t n);
        Matrix(const Matrix& matrix);
        ~Matrix();
        double operator()(size_t m, size_t n) const; // read only
        double& operator()(size_t m, size_t n); // write
        size_t getNumOfRows() const;
        size_t getNumOfColumns() const;
        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
        Matrix& operator=(const Matrix& matrix);
};