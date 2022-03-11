#pragma once
#include <cassert>
#include <cmath>
#include <array>
#include <stack>
#include <initializer_list>

namespace rt_math
{

constexpr float EPSILON = 0.00001f;
inline bool eq_f(float const a, float const b)
{
    return std::abs(a - b) < EPSILON;
}

template <typename T>
bool eq(T lhs, T rhs)
{
    return lhs == rhs;
}

template < >
inline bool eq(const float lhs, const float rhs)
{
    return eq_f(lhs, rhs);
}

struct tuple
{
    float x; float y; float z; float w;

    [[nodiscard]]
    bool IsPoint() const
    {
        return w == 1.0f;
    }

    [[nodiscard]]
    bool IsVector() const
    {
        return w == 0.0f;
    }

    [[nodiscard]]
    float magnitude() const
    {
        // since C++11 (and C++17 adds 3 parameters)
        // std function for square root of sum of squares
        return std::hypot(this->x, this->y, this->z);
    }

    /*
     * This is a good example of why class inheritance for Point and Vector types do not make sense.
     *
     * Adding w=1 (point) to a w=0 (vector) produces a point.
     * Adding w=0 (vector) to a w=0 (vector) produces another vector.
     * Adding w=1 (point) to a w=1 (point) produces w=2, undefined here,
     *   which matches the fact that mathematically cannot add point and a point.
     */
    tuple operator+(const tuple &rhs) const
    {
        return tuple(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }

    /*
     * Subtracting w=1 (point) - w=1 (point) gives w=0 (vector), as expected mathematically,
     *   giving __direction__ between two points.
     *
     * Useful for chapter 6 - finding vector pointing to light source.
     */
    tuple operator-(const tuple &rhs) const
    {
        return tuple(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }

    /*
     * Negating vector. Useful for chapter 6 - shading.
     */
    tuple operator-() const
    {
        return tuple(0 - x, 0 - y, 0 - z, 0 - w);
    }

    tuple operator*(float const a) const
    {
        return tuple(x * a, y * a, z * a, w * a);
    }
    tuple operator/(float const a) const
    {
        return tuple(x / a, y / a, z / a, w / a);
    }
};

// typedef tuple point;
inline bool operator==(const tuple &lhs, const tuple &rhs)
{
    return eq_f(lhs.x, rhs.x)
        && eq_f(lhs.y, rhs.y)
        && eq_f(lhs.z, rhs.z)
        && eq_f(lhs.w, rhs.w);
}

inline bool operator!=(const tuple &lhs, const tuple &rhs)
{
    return !(lhs == rhs);
}

tuple inline vector(const float x, const float y, const float z)
{
    return tuple(x, y, z, 0);
}
tuple inline point(const float x, const float y, const float z)
{
    return tuple(x, y, z, 1);
}

inline float dot(const tuple &a, const tuple &b)
{
    assert(a.IsVector() && b.IsVector());

    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline tuple cross(const tuple &a, const tuple &b)
{
    assert(a.IsVector() && b.IsVector());

    return vector(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

inline tuple normalize(const tuple &v)
{
    assert(v.IsVector());

    const float magnitude = v.magnitude();
    return vector(
        v.x / magnitude,
        v.y / magnitude,
        v.z / magnitude
    );
}

struct color
{
    float red; float green; float blue;

    color operator+(const color &rhs) const
    {
        return color(red + rhs.red, green + rhs.green, blue + rhs.blue);
    }
    color operator-(const color &rhs) const
    {
        return color(red - rhs.red, green - rhs.green, blue - rhs.blue);
    }

    color operator*(const float rhs) const
    {
        return color(red * rhs, green * rhs, blue * rhs);
    }

    /*
     * Hadamard product
     */
    color operator*(const color &rhs) const
    {
        return color(red * rhs.red, green * rhs.green, blue * rhs.blue);
    }
};

inline bool operator==(const color &lhs, const color &rhs)
{
    return eq_f(lhs.red, rhs.red)
        && eq_f(lhs.green, rhs.green)
        && eq_f(lhs.blue, rhs.blue);
} 
inline bool operator!=(const color &lhs, const color &rhs)
{
    return !(lhs == rhs);
}

template <size_t N>
class Matrix
{
public:
    Matrix(const std::initializer_list<float> args)
    {
        assert(args.size() == N * N);

        int i = 0;
        for (float cell : args)
        {
            matrix_[i] = cell;
            i++;
        }
    }
    Matrix(std::array<float, N*N> &&values) : matrix_(std::move(values)) {}
    Matrix(const std::array<float, N*N> &values) : matrix_(std::move(values)) {}

    /*
     * Could optionally generalize into hardcoded versions of identity matrices
     */
    static Matrix identity_matrix()
    {
        std::array<float, N * N> tmpM = {};
        for (size_t row = 0; row < N; ++row)
        {
            for (size_t column = 0; column < N; ++column)
            {
                tmpM[row * N + column] = (row == column ? 1.0f : 0.0f);
            }
        }

        return Matrix<N>(tmpM);
    }

    [[nodiscard]]
    float at(const size_t row, const size_t column) const
    {
        const size_t index = row * N + column;
        return matrix_[index];
    }

    [[nodiscard]]
    float determinant() const;

    [[nodiscard]]
    Matrix<N-1> submatrix(const unsigned int row, const unsigned int column) const
    {
        std::array<float, (N-1) * (N-1)> tmpM;

        const size_t rowIndexBegin = row * N;
        const size_t rowIndexEnd = row * N + N;

        size_t newIndex = 0;
        size_t columnCounter = 0;
        for (size_t i = 0; i < N * N; ++i)
        {
            if (i >= rowIndexBegin && i < rowIndexEnd)
            {
                columnCounter = 0;
                continue;
            }

            if (columnCounter == N)
            {
                columnCounter = 0;
            }

            if (columnCounter == column)
            {
                ++columnCounter;
                continue;
            }

            tmpM[newIndex] = matrix_[i];
            ++newIndex;
            ++columnCounter;
        }

        return Matrix<N-1>(tmpM);
    }

    [[nodiscard]]
    float minor(const unsigned int row, const unsigned int column) const
    {
        return this->submatrix(row, column).determinant();
    }

    [[nodiscard]]
    float cofactor(const unsigned int row, const unsigned int column) const
    {
        float minor = this->minor(row, column);
        if ((row + column) % 2 != 0)
        {
            minor = -minor;
        }

        return minor;
    }

    [[nodiscard]]
    bool is_invertible() const
    {
        return this->determinant() != 0.0f;
    }

    [[nodiscard]]
    Matrix<N> inverse() const
    {
        std::array<float, N*N> tmpCofactors = {};

        size_t i = 0;
        for (unsigned int row = 0; row < N; ++row)
        {
            for (unsigned int column = 0; column < N; ++column)
            {
                tmpCofactors[i] = this->cofactor(row, column);

                i++;
            }
        }

        Matrix<N> transposed_cofactors = transpose(Matrix<N>(tmpCofactors));
        float determinant = this->determinant();
        assert(determinant != 0);

        constexpr size_t upper_index = N * N;
        for (i = 0; i < upper_index; ++i)
        {
            transposed_cofactors.matrix_[i] = transposed_cofactors.matrix_[i] / determinant;
        }


        return transposed_cofactors;
    }

    Matrix operator*(const Matrix &rhs) const
    {
        std::array<float, N*N> tmpM = {};
        size_t i = 0;
        for (size_t row = 0; row < N; ++row)
        {
            for (size_t column = 0; column < N; ++column)
            {
                float sum = 0;
                for (size_t columnIndex = 0; columnIndex < N; ++columnIndex)
                {
                    sum += at(row, columnIndex) * rhs.at(columnIndex, column);
                }

                tmpM[i] = sum;
                i++;
            }
        }

        return Matrix<N>(tmpM);
    }

    /*
     * Treating tuple as a single COLUMN matrix
     */
    tuple operator*(const tuple &rhs) const
    {
        static_assert(N == 4,
            "Our tuples are all size 4. Can only multiply 4x4 matrices.");

        return tuple{
            .x = matrix_[0] * rhs.x + matrix_[1] * rhs.y + matrix_[2] * rhs.z + matrix_[3] * rhs.w,
            .y = matrix_[4] * rhs.x + matrix_[5] * rhs.y + matrix_[6] * rhs.z + matrix_[7] * rhs.w,
            .z = matrix_[8] * rhs.x + matrix_[9] * rhs.y + matrix_[10] * rhs.z + matrix_[11] * rhs.w,
            .w = matrix_[12] * rhs.x + matrix_[13] * rhs.y + matrix_[14] * rhs.z + matrix_[15] * rhs.w,
        };
    }

    template <size_t Nn>
    friend bool operator==(const Matrix<Nn> &lhs, const Matrix<Nn> &rhs);

private:
    std::array<float, N*N> matrix_ = {};
};

template < >
inline float Matrix<2>::determinant() const
{
    return matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
}

template < >
inline float Matrix<3>::determinant() const
{
    return
        matrix_[0] * this->cofactor(0, 0) +
        matrix_[1] * this->cofactor(0, 1) + 
        matrix_[2] * this->cofactor(0, 2);
}

template < >
inline float Matrix<4>::determinant() const
{
    return
        matrix_[0] * this->cofactor(0, 0) +
        matrix_[1] * this->cofactor(0, 1) + 
        matrix_[2] * this->cofactor(0, 2) +
        matrix_[3] * this->cofactor(0, 3);
}


template <size_t Nn>
bool operator==(const Matrix<Nn> &lhs, const Matrix<Nn> &rhs)
{
    return std::equal(
        lhs.matrix_.begin(), lhs.matrix_.end(),
        rhs.matrix_.begin(),
        [](const float& left, const float& right)
        {
            return rt_math::eq_f(left, right);
        }
    );
}

inline Matrix<4> identity_matrix = Matrix<4> {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

/*
 * Could be neat if did not have to do multiplication by identity matrix,
 * just check Matrix.IsIdentity flag that could be set during initialization
 */
template <size_t N>
Matrix<N> transpose(Matrix<N> matrix)
{
    std::array<float, N * N> tmpM = {};
    for (size_t row = 0; row < N; ++row)
    {
        for (size_t column = 0; column < N; ++column)
        {
            tmpM[column * N + row] = matrix.at(row, column);
        }
    }

    return Matrix<N>(tmpM);
}

}


// ====== GEOMETRIC TRANSFORMATIONS =======
inline rt_math::Matrix<4> translation(const float x, const float y, const float z)
{
    return rt_math::Matrix<4> {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };
}

inline rt_math::Matrix<4> scaling(const float x, const float y, const float z)
{
    return rt_math::Matrix<4> {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
}

inline rt_math::Matrix<4> reflection()
{
    return rt_math::Matrix<4> {
        -1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1
    };
}

inline rt_math::Matrix<4> rotation_x(const float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    return rt_math::Matrix<4> {
        1, 0,      0, 0,
        0, cos, -sin, 0,
        0, sin,  cos, 0,
        0, 0,      0, 1
    };
}

inline rt_math::Matrix<4> rotation_y(const float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    return rt_math::Matrix<4> {
        cos,  0, sin, 0,
        0,    1,   0, 0,
        -sin, 0, cos, 0,
        0,    0,   0, 1
    };
}

inline rt_math::Matrix<4> rotation_z(const float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    return rt_math::Matrix<4> {
        cos, -sin, 0, 0,
        sin,  cos, 0, 0,
        0,      0, 1, 0,
        0,      0, 0, 1
    };
}
