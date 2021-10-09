#pragma once
#include <cmath>
#include <cassert>

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

		tuple(float const x, float const y, float const z, float const w)
			: x(x), y(y), z(z), w(w) {}

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

		friend bool operator==(const tuple &lhs, const tuple &rhs)
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

	tuple inline point(float const x, float const y, float const z)
	{
		return tuple(x, y, z, 1);
	}

	tuple inline vector(float const x, float const y, float const z)
	{
		return tuple(x, y, z, 0);
	}
}
