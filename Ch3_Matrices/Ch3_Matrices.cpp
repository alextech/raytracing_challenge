// Ch3_Matrices.cpp : Experiments with matrix properties

#include <iostream>
#include "../Math/Math.h"

using namespace rt_math;


std::ostream& operator<<(std::ostream &os, const Matrix<4> &matrix)
{
    for(size_t row = 0; row < 4; ++row)
    {
        for (size_t column = 0; column < 4; ++column)
        {
            
            os << matrix.at(row, column) << "  ";
        }

        os << std::endl;
    }

    return os;
}

std::ostream& operator<<(std::ostream &os, const tuple &tuple)
{
    os << "[ " << tuple.x << " " << tuple.y << " " << tuple.z << " " << tuple.w << " ]";

    return os;
}

int main()
{
    std::cout << std::endl << "1. Inverse of identity matrix:" << std::endl;
    Matrix<4> identity = Matrix<4>::identity_matrix();
    std::cout << identity.inverse();

    std::cout << std::endl << "2. Multiply by its inverse:" << std::endl;
    const Matrix<4> A = Matrix<4> {
		6,  4, 4,  4,
		5,  5, 7,  6,
		4, -9, 3, -7,
		9,  1, 7, -6
    };
    std::cout << "A = " << std::endl << A << std::endl;
    std::cout << " = "  << std::endl << A * A.inverse();
    // becomes identity matrix, but hard to see right away because of long float indecies.

    std::cout << std::endl << "3. inverse of transpose vs. transpose of inverse:" << std::endl;
    std::cout << "inverse of transpose = " << std::endl << transpose(A).inverse() << std::endl;
    std::cout << "transpose of inverse = " << std::endl << transpose(A.inverse()) << std::endl;

    std::cout << std::endl << "4. multiply modified identity by tuple:" << std::endl;
    std::cout << "Identity times tuple = " << std::endl;
    const tuple tuple = rt_math::tuple { .x = 1.0f, .y = 2.0f, .z = 3.0f, .w = 4.0f };
    std::cout << identity_matrix * tuple;

    const Matrix<4> modified_identity = Matrix<4> {
        1, 0, 0, 2,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    std::cout << "Modified identity: " << std::endl << modified_identity << std::endl;
    std::cout << "Modified times tuple = " << std::endl << modified_identity * tuple << std::endl;

}

