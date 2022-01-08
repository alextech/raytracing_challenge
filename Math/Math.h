#pragma once
#include <cassert>
#include <cmath>
#include <vector>
#include <array>
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

			[[nodiscard]]
			float at(const size_t row, const size_t column) const
			{
				const size_t index = row * N + column;
				return matrix_[index];
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

			template <size_t Nn>
			friend bool operator==(const Matrix<Nn> &lhs, const Matrix<Nn> &rhs);

		private:
			std::array<float, N*N> matrix_ = {};
	};

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
}
