#include "Matrix.h"
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
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < m; ++i) {
        arr[i] = new double[n];
        if (!arr[i]) {
            throw std::bad_alloc();
        }
    }

    //Initialize array to zeroes
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
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

double Matrix::operator()(size_t m, size_t n) const
{
    if (this->m >= m && this->n >= n)
        return arr[m][n];
    else {
        throw std::invalid_argument("There's no such element in the matrix.");
    }
}

double& Matrix::operator()(size_t m, size_t n)
{
    if (this->m >= m && this->n >= n)
        return arr[m][n];
    else {
        throw std::invalid_argument("There's no such element in the matrix.");
    }
}

size_t Matrix::getNumOfRows() const
{
    return m;
}

size_t Matrix::getNumOfColumns() const
{
    return n;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{   
    size_t m = matrix.getNumOfRows();
    size_t n = matrix.getNumOfColumns();

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            os << matrix(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}