#pragma once
#include <cassert>
#include <cmath>
#include <vector>

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

	inline float dot(const tuple& a, const tuple& b)
	{
		assert(a.IsVector() && b.IsVector());

		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline tuple cross(const tuple& a, const tuple& b)
	{
		assert(a.IsVector() && b.IsVector());

		return vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	inline tuple normalize(const tuple& v)
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

	inline bool operator==(const color& lhs, const color& rhs)
	{
		return eq_f(lhs.red, rhs.red)
			&& eq_f(lhs.green, rhs.green)
			&& eq_f(lhs.blue, rhs.blue);
	} 
	inline bool operator!=(const color& lhs, const color& rhs)
	{
		return !(lhs == rhs);
	}

	class M_4x4
	{
		public:
			M_4x4(
				 float r1_c1,
				 float r1_c2,
				 float r1_c3,
				 float r1_c4,
				 float r2_c1,
				 float r2_c2,
				 float r2_c3,
				 float r2_c4,
				 float r3_c1,
				 float r3_c2,
				 float r3_c3,
				 float r3_c4,
				 float r4_c1,
				 float r4_c2,
				 float r4_c3,
				 float r4_c4
			);

			M_4x4(std::vector<float> &&values) : matrix_(std::move(values)) {}
			M_4x4(const std::vector<float> &values) {}

			M_4x4 operator*(const rt_math::M_4x4 &rhs) const;

			[[nodiscard]]
			float at(int row, int column) const;

			friend bool operator==(const M_4x4 &lhs, const M_4x4 &rhs);

		private:
			// consider https://docs.microsoft.com/en-us/cpp/standard-library/array-class-stl?view=msvc-160
			std::vector<float> matrix_;
	};

	bool operator==(const M_4x4 &lhs, const M_4x4 &rhs);

	class M_2x2
	{
		public:
			M_2x2(
				 float r1_c1,
				 float r1_c2,
				 float r2_c1,
				 float r2_c2
			);

			[[nodiscard]]
			float at(int row, int column) const;
		private:
			// consider https://docs.microsoft.com/en-us/cpp/standard-library/array-class-stl?view=msvc-160
			std::vector<float> matrix_;
	};

	class M_3x3
	{
		public:
			M_3x3(
				 float r1_c1,
				 float r1_c2,
				 float r1_c3,
				 float r2_c1,
				 float r2_c2,
				 float r2_c3,
				 float r3_c1,
				 float r3_c2,
				 float r3_c3
			);

			[[nodiscard]]
			float at(int row, int column) const;

		private:
			// consider https://docs.microsoft.com/en-us/cpp/standard-library/array-class-stl?view=msvc-160
			std::vector<float> matrix_;
	};
}
