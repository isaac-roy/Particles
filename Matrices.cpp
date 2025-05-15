#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Matrices.h"

using namespace std;

namespace Matrices
{
    ///Construct a matrix of the specified size.
    ///Initialize each element to 0.
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;
        a.resize(rows);
        for(int i = 0; i < rows; i++)
        {
            a[i].resize(cols, 0.0);
        }
    }

    ///Add each corresponding element.
    ///usage: c = a + b;
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if(a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw "Matrix dimensions don't match for addition";
        }

        Matrix c(a.getRows(), a.getCols());

        for(int i = 0; i < c.getRows(); i++)
        {
            for(int j = 0; j < c.getCols(); j++)
            {
                c(i, j) = a(i, j) + b(i, j);
            }
        }

        return c;
    }

    ///Matrix multiply. See description.
    ///usage: c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw "Matrix dimensions don't match for multiplication";
        }

        Matrix c(a.getRows(), b.getCols());

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < b.getCols(); ++j)
            {
                c(i, j) = 0;
                for (int k = 0; k < a.getCols(); ++k)
                {
                    c(i, j) += a(i, k) * b(k, j);
                }
            }
        }

        return c;
    }

    ///Matrix comparison. See description.
    ///usage: a == b
    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if (a(i, j) != b(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }

    ///Matrix comparison. See description.
    ///usage: a != b
    bool operator!=(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return true;
        }

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if (a(i, j) != b(i, j))
                {
                    return true;
                }
            }
        }

        return false;
    }

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                os << a(i, j);
                if (j != a.getCols() - 1)
                    os << ' ';
            }
            os << '\n';
        }
        return os;
    }

    ///2D rotation matrix
    ///usage: A = R * A rotates A theta radians counter-clockwise

    ///Call the parent constructor to create a 2x2 matrix
    ///Then assign each element as follows:
    /*
    cos(theta) -sin(theta)
    sin(theta) cos(theta)
    */
    ///theta represents the angle of rotation in radians, counter-clockwise
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }

    ///2D scaling matrix
    ///usage: A = S * A expands or contracts A by the specified scaling factor

    ///Call the parent constructor to create a 2x2 matrix
    ///Then assign each element as follows:
    /*
    scale 0
    0 scale
    */
    ///scale represents the size multiplier
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0.0;
        a[1][0] = 0.0;
        a[1][1] = scale;
    }

    ///2D Translation matrix
    ///usage: A = T + A will shift all coordinates of A by (xShift, yShift)

    ///Call the parent constructor to create a 2xn matrix
    ///Then assign each element as follows:
    /*
    xShift xShift xShift ...
    yShift yShift yShift ...
    */
    ///paramaters are xShift, yShift, and nCols
    ///nCols represents the number of columns in the matrix
    ///where each column contains one (x,y) coordinate pair
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for(int j = 0; j < nCols; j++)
        {
            a[0][j] = xShift;
            a[1][j] = yShift;
        }
    }
}   
