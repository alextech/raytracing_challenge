#include <cassert>
#include "Math.h"

// ==========================================
//             TUPLE DEFINITION
// ==========================================

// ==========================================
//             OPERATIONS WITH TUPLES
// ==========================================
bool rt_math::operator==(const tuple &lhs, const tuple &rhs)
{
	return eq_f(lhs.x, rhs.x)
		&& eq_f(lhs.y, rhs.y)
		&& eq_f(lhs.z, rhs.z)
		&& eq_f(lhs.w, rhs.w);
}

bool rt_math::operator!=(const tuple &lhs, const tuple &rhs)
{
	return !(lhs == rhs);
}

rt_math::tuple rt_math::normalize(const tuple &v)
{
	assert(v.IsVector());

	const float magnitude = v.magnitude();
	return vector(
		v.x / magnitude,
		v.y / magnitude,
		v.z / magnitude
	);
}

float rt_math::dot(const tuple &a, const tuple &b)
{
	assert(a.IsVector() && b.IsVector());

	return a.x * b.x + a.y * b.y + a.z * b.z;
}

rt_math::tuple rt_math::cross(const rt_math::tuple &a, const rt_math::tuple &b)
{
	assert(a.IsVector() && b.IsVector());

	return vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

// ======================================
//             OPERATIONS WITH COLOR
// ======================================


bool rt_math::operator==(const color &lhs, const color &rhs)
{
	return eq_f(lhs.red, rhs.red)
		&& eq_f(lhs.green, rhs.green)
		&& eq_f(lhs.blue, rhs.blue);
}

bool rt_math::operator!=(const color& lhs, const color& rhs)
{
	return !(lhs == rhs);
}
