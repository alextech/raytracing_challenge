#pragma once
#include <cmath>
#include <cassert>
#include <vector>

namespace rt_math
{
	constexpr float EPSILON = 0.00001f;
	inline bool eq_f(float const a, float const b)
	{
		return std::abs(a - b) < EPSILON;
	}

	struct tuple;
	tuple inline vector(float x, float y, float z);
	tuple inline point(float x, float y, float z);

	struct tuple
	{
		float x; float y; float z; float w;

		// tuple(float const x, float const y, float const z, float const w)
		// 	: x(x), y(y), z(z), w(w) {}

		bool IsPoint() const
		{
			return w == 1.0f;
		}

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

		friend bool operator==(const tuple lhs, const tuple &rhs)
		{
			return eq_f(lhs.x, rhs.x)
				&& eq_f(lhs.y, rhs.y)
				&& eq_f(lhs.z, rhs.z)
				&& eq_f(lhs.w, rhs.w);
		}

		friend bool operator!=(const tuple &lhs, const tuple &rhs)
		{
			return !(lhs == rhs);
		}

		/*
		 * This is a good example of why class inheritance for Point and Vector types do not make sense.
		 *
		 * Adding w=1 (point) to a w=0 (vector) produces a point.
		 * Adding w=0 (vector) to a w=0 (vector) produces another vector.
		 * Adding w=1 (point) to a w=1 (point) produces w=2, undefined here,
		 *   which matches the fact that mathematically cannot add point and a point.
		 */
		friend tuple operator+(const tuple &lhs, const tuple &rhs)
		{
			return tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
		}

		/*
		 * Subtracting w=1 (point) - w=1 (point) gives w=0 (vector), as expected mathematically,
		 *   giving __direction__ between two points.
		 *
		 * Useful for chapter 6 - finding vector pointing to light source.
		 */
		friend tuple operator-(const tuple &lhs, const tuple &rhs)
		{
			return tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
		}

		/*
		 * Negating vector. Useful for chapter 6 - shading.
		 */
		friend tuple operator-(const tuple &rhs)
		{
			return tuple(0 - rhs.x, 0 - rhs.y, 0 - rhs.z, 0 - rhs.w);
		}

		friend tuple operator*(const tuple &lhs, float const a)
		{
			return tuple(lhs.x * a, lhs.y * a, lhs.z * a, lhs.w * a);
		}

		friend tuple operator/(const tuple &lhs, float const a)
		{
			return tuple(lhs.x / a, lhs.y / a, lhs.z / a, lhs.w / a);
		}

		friend tuple normalize(const tuple &v)
		{
			assert(v.IsVector());

			const float magnitude = v.magnitude();
			return vector(v.x / magnitude,
						  v.y / magnitude,
						  v.z / magnitude
			);
		}

		friend float dot(const tuple &a, const tuple &b)
		{
			assert(a.IsVector() && b.IsVector());

			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		friend tuple cross(const tuple &a, const tuple &b)
		{
			assert(a.IsVector() && b.IsVector());

			return vector(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			);
		}

	};

	struct color
	{
		float red; float green; float blue;

		friend color operator+(const color &c1, const color &c2)
		{
			return color{
				.red = c1.red + c2.red,
				.green = c1.green + c2.green,
				.blue = c1.blue + c2.blue
			};
		}

		friend color operator-(const color &c1, const color &c2)
		{
			return color{
				.red = c1.red - c2.red,
				.green = c1.green - c2.green,
				.blue = c1.blue - c2.blue
			};
		}

		friend bool operator==(const color &lhs, const color &rhs)
		{
			return eq_f(lhs.red, rhs.red)
				&& eq_f(lhs.green, rhs.green)
				&& eq_f(lhs.blue, rhs.blue);
		}

		friend bool operator!=(const color &lhs, const color &rhs)
		{
			return !(lhs == rhs);
		}

		friend color operator*(const color &lhs, const float rhs)
		{
			return color(lhs.red * rhs, lhs.green * rhs, lhs.blue * rhs);
		}

		/*
		 * Hadamard product
		 */
		friend color operator*(const color &lhs, const color &rhs)
		{
			return color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue);
		}
	};

	tuple inline point(float const x, float const y, float const z)
	{
		// return tuple(x, y, z, 1);

		return tuple {
			.x = x,
			.y = y,
			.z = z,
			.w = 1
		};
	}

	tuple inline vector(float const x, float const y, float const z)
	{
		return tuple(x, y, z, 0);
	}

	template <typename T>
	class M_4x4
	{
		public:
			M_4x4(
				T r1_c1,
				T r1_c2,
				T r1_c3,
				T r1_c4,
				T r2_c1,
				T r2_c2,
				T r2_c3,
				T r2_c4,
				T r3_c1,
				T r3_c2,
				T r3_c3,
				T r3_c4,
				T r4_c1,
				T r4_c2,
				T r4_c3,
				T r4_c4
			);

			T at(const int row, const int column) const;
		private:
			std::vector<T> matrix_;
	};

	template <typename T>
	class M_2x2
	{
		public:
			M_2x2(
				const T r1_c1,
				const T r1_c2,
				const T r2_c1,
				const T r2_c2
			);

			T at(const int row, const int column) const;
		private:
			std::vector<T> matrix_;
	};

	template <typename T>
	class M_3x3
	{
		public:
			M_3x3(
				const T r1_c1,
				const T r1_c2,
				const T r1_c3,
				const T r2_c1,
				const T r2_c2,
				const T r2_c3,
				const T r3_c1,
				const T r3_c2,
				const T r3_c3
			);

			T at(const int row, const int column) const;
		private:
			std::vector<T> matrix_;
	};
}
