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

Matrix::Matrix(const Matrix& matrix)
{   
    m = matrix.getNumOfRows();
    n = matrix.getNumOfColumns();
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
    
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            arr[i][j] = matrix(i, j);
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
            os << matrix(i, j) << "\t";
        }
        os << "\n";
    }
    return os;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
    for (unsigned int i = 0; i < m; ++i) {
        delete[] arr[i];
    }
    delete[] arr;

    m = matrix.getNumOfRows();
    n = matrix.getNumOfColumns();
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
    
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            arr[i][j] = matrix(i, j);
        }
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
    if (m != matrix.getNumOfRows() || n != matrix.getNumOfColumns()) {
        throw std::invalid_argument("Matrices have to be the same size to add.");
    }
    Matrix sum = *this;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            sum(i, j) += matrix(i, j);
        }
    }
    return sum;
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
    if (m != matrix.getNumOfRows() || n != matrix.getNumOfColumns()) {
        throw std::invalid_argument("Matrices have to be the same size to add.");
    }
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            this->arr[i][j] += matrix(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
    if (m != matrix.getNumOfRows() || n != matrix.getNumOfColumns()) {
        throw std::invalid_argument("Matrices have to be the same size to add.");
    }
    Matrix diff = *this;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            diff(i, j) -= matrix(i, j);
        }
    }
    return diff;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
    if (m != matrix.getNumOfRows() || n != matrix.getNumOfColumns()) {
        throw std::invalid_argument("Matrices have to be the same size to add.");
    }
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            this->arr[i][j] -= matrix(i, j);
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& matrix)
{
    if (n != matrix.getNumOfRows()) {
        std::string err = "Matrices can be multiplied only if "
                          "the number of columns of the first "
                          "is equal to the number of rows of the second.";
        throw std::invalid_argument(err);
    }
    size_t p = matrix.getNumOfColumns();
    Matrix product(m, p);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            double element = 0;
            for (size_t k = 0; k < n; ++k) {
                element += arr[i][k] * matrix(k, j);
            }
            product(i, j) = element;
        }
    }
    return product;
}

Matrix& Matrix::operator*=(const Matrix& matrix)
{
    *this = *this * matrix;
    return *this;
}

std::istream& operator>>(std::istream& is, Matrix& matrix)
{  
    size_t numOfRows = 0, numOfColumns = 0, textSize = 10;
    std::string* text = new std::string[textSize];
    std::string line = "";

    while (!is.eof()) {
        getline(is, line);
        if (line == "") {
            break;
        }
        if (numOfRows == textSize) {
            size_t newTextSize = (textSize + 1) * 2;
            std::string* newText = new std::string[newTextSize];
            for (size_t i = 0; i < textSize; ++i) {
                newText[i] = text[i];
            }
            delete[] text;
            text = newText;
            textSize = newTextSize;
        }
        text[numOfRows++] = line;
    }

    line = text[0];
    size_t elementSize = 0;
    for (char c : line) {
        if (!isblank(c)) {
            elementSize++;
        }
        else if (elementSize > 0) {
            elementSize = 0;
            numOfColumns++;
        }
    }
    if (elementSize > 0) {
        elementSize = 0;
        numOfColumns++;
    }

    Matrix input(numOfRows, numOfColumns);
    for (size_t row = 0; row < numOfRows; ++row) {
        line = text[row];
        elementSize = 0;
        size_t column = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            if (!isblank(line[i])) {
                elementSize++;
            }
            else if (elementSize > 0) {
                if (column == numOfColumns) {
                    std::string err = "Matrix has to have the same number "
                                      "of columns per each row.";
                    throw std::invalid_argument(err);
                }
                std::string element = line.substr(i - elementSize, elementSize);
                double num = std::stod(element);
                input(row, column++) = num;
                elementSize = 0;
            }
        }
        if (column == numOfColumns) {
                    std::string err = "Matrix has to have the same number "
                                      "of columns per each row.";
                    throw std::invalid_argument(err);
                }
                std::string element = line.substr(line.size() - elementSize, elementSize);
                double num = std::stod(element);
                input(row, column++) = num;
                elementSize = 0;
            }
    matrix = input;
    return is;
}
    