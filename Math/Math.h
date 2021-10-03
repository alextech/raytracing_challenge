#pragma once
#include <cmath>

namespace rt_math
{
	constexpr float EPSILON = 0.00001f;
	inline bool eq_f(float const a, float const b)
	{
		return std::abs(a - b) < EPSILON;
	}

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

		friend bool operator==(const tuple& lhs, const tuple& rhs)
		{
			return eq_f(lhs.x, rhs.x)
				&& eq_f(lhs.y, rhs.y)
				&& eq_f(lhs.z, rhs.z)
				&& eq_f(lhs.w, rhs.w);
		}

		friend bool operator!=(const tuple& lhs, const tuple& rhs)
		{
			return !(lhs == rhs);
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
