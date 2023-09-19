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
        Matrix operator+(const Matrix& matrix) const;
        Matrix& operator+=(const Matrix& matrix);
        Matrix operator-(const Matrix& matrix) const;
        Matrix& operator-=(const Matrix& matrix);
        Matrix operator*(const Matrix& matrix);
        Matrix& operator*=(const Matrix& matrix);
        friend std::istream& operator>>(std::istream& is, Matrix& m);
        friend void readText(std::istream& is, std::string* text, 
                                size_t& numOfRows, size_t& textSize);
        friend size_t countNumOfColumns(std::string line);
};

std::string* seperateElementsInAString(std::string line, size_t numOfElements);