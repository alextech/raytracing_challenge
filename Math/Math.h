#pragma once
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
		bool IsPoint() const;

		[[nodiscard]]
		bool IsVector() const;

		[[nodiscard]]
		float magnitude() const;

		friend bool operator==(const tuple lhs, const tuple &rhs);
		friend bool operator!=(const tuple &lhs, const tuple &rhs);
		/*
		 * This is a good example of why class inheritance for Point and Vector types do not make sense.
		 *
		 * Adding w=1 (point) to a w=0 (vector) produces a point.
		 * Adding w=0 (vector) to a w=0 (vector) produces another vector.
		 * Adding w=1 (point) to a w=1 (point) produces w=2, undefined here,
		 *   which matches the fact that mathematically cannot add point and a point.
		 */
		friend tuple operator+(const tuple &lhs, const tuple &rhs);
		friend tuple operator-(const tuple &lhs, const tuple &rhs);
		friend tuple operator-(const tuple &rhs);
		friend tuple operator*(const tuple &lhs, float const a);
		friend tuple operator/(const tuple &lhs, float const a);
		friend tuple normalize(const tuple &v);
		friend float dot(const tuple &a, const tuple &b);
		friend tuple cross(const tuple &a, const tuple &b);
	};

	float dot(const tuple& a, const tuple& b);
	tuple cross(const tuple& a, const tuple& b);

	tuple inline vector(const float x, const float y, const float z)
	{
		// return tuple(x, y, z, 1);

		return tuple{
			.x = x,
			.y = y,
			.z = z,
			.w = 0
		};
	}
	tuple inline point(const float x, const float y, const float z)
	{
		return tuple{
			.x = x,
			.y = y,
			.z = z,
			.w = 1
		};
	}

	struct color
	{
		float red; float green; float blue;

		friend color operator+(const color& c1, const color& c2);
		friend color operator-(const color& c1, const color& c2);
		friend bool operator==(const color& lhs, const color& rhs);
		friend bool operator!=(const color &lhs, const color &rhs);
		friend color operator*(const color &lhs, const float rhs);

		/*
		 * Hadamard product
		 */
		friend color operator*(const color &lhs, const color &rhs);
	};

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
			explicit M_4x4(const std::vector<T>& values);
			explicit M_4x4(std::vector<T>&& values);

			T at(const int row, const int column) const;

			friend bool operator==(const M_4x4& lhs, const M_4x4& rhs)
			{
				return std::equal(
					lhs.matrix_.begin(), lhs.matrix_.end(),
					rhs.matrix_.begin(),
					[](const T& left, const T& right)
					{
						return eq(left, right);
					}
				);
			}

		private:
			// consider https://docs.microsoft.com/en-us/cpp/standard-library/array-class-stl?view=msvc-160
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
			// consider https://docs.microsoft.com/en-us/cpp/standard-library/array-class-stl?view=msvc-160
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
			// consider https://docs.microsoft.com/en-us/cpp/standard-library/array-class-stl?view=msvc-160
			std::vector<T> matrix_;
	};
}

template <typename T>
rt_math::M_4x4<T> operator*(const rt_math::M_4x4<T>& lhs, const rt_math::M_4x4<T>& rhs);
