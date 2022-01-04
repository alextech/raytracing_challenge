#include <cassert>
#include "Math.h"

// ==========================================
//             TUPLE DEFINITION
// ==========================================
bool rt_math::tuple::IsPoint() const
{
	return w == 1.0f;
}

bool rt_math::tuple::IsVector() const
{
	return w == 0.0f;
}


// ==========================================
//             OPERATIONS WITH TUPLES
// ==========================================
bool rt_math::operator==(const tuple lhs, const tuple& rhs)
{
	return eq_f(lhs.x, rhs.x)
		&& eq_f(lhs.y, rhs.y)
		&& eq_f(lhs.z, rhs.z)
		&& eq_f(lhs.w, rhs.w);
}

bool rt_math::operator!=(const tuple& lhs, const tuple& rhs)
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
rt_math::tuple rt_math::operator+(const tuple& lhs, const tuple& rhs)
{
	return tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}


/*
 * Subtracting w=1 (point) - w=1 (point) gives w=0 (vector), as expected mathematically,
 *   giving __direction__ between two points.
 *
 * Useful for chapter 6 - finding vector pointing to light source.
 */
rt_math::tuple rt_math::operator-(const tuple& lhs, const tuple& rhs)
{
	return tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

/*
 * Negating vector. Useful for chapter 6 - shading.
 */
rt_math::tuple rt_math::operator-(const tuple& rhs)
{
	return tuple(0 - rhs.x, 0 - rhs.y, 0 - rhs.z, 0 - rhs.w);
}

rt_math::tuple rt_math::operator*(const tuple& lhs, float const a)
{
	return tuple(lhs.x * a, lhs.y * a, lhs.z * a, lhs.w * a);
}

rt_math::tuple rt_math::operator/(const tuple& lhs, float const a)
{
	return tuple(lhs.x / a, lhs.y / a, lhs.z / a, lhs.w / a);
}

rt_math::tuple rt_math::normalize(const tuple& v)
{
	assert(v.IsVector());

	const float magnitude = v.magnitude();
	return vector(
		v.x / magnitude,
		v.y / magnitude,
		v.z / magnitude
	);
}

float rt_math::dot(const tuple& a, const tuple& b)
{
	assert(a.IsVector() && b.IsVector());

	return a.x * b.x + a.y * b.y + a.z * b.z;
}

rt_math::tuple rt_math::cross(const rt_math::tuple& a, const rt_math::tuple& b)
{
	assert(a.IsVector() && b.IsVector());

	return vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float rt_math::tuple::magnitude() const
{
	// since C++11 (and C++17 adds 3 parameters)
	// std function for square root of sum of squares
	return std::hypot(this->x, this->y, this->z);
}


rt_math::color operator*(const rt_math::color lhs, const float rhs)
{
	return rt_math::color(lhs.red * rhs, lhs.green * rhs, lhs.blue * rhs);
}


// ======================================
//             OPERATIONS WITH COLOR
// ======================================

rt_math::color rt_math::operator+(const color& c1, const color& c2)
{
	return color{
		.red = c1.red + c2.red,
		.green = c1.green + c2.green,
		.blue = c1.blue + c2.blue
	};
}

rt_math::color rt_math::operator-(const color& c1, const color& c2)
{
	return color{
		.red = c1.red - c2.red,
		.green = c1.green - c2.green,
		.blue = c1.blue - c2.blue
	};
}

bool rt_math::operator==(const color& lhs, const color& rhs)
{
	return eq_f(lhs.red, rhs.red)
		&& eq_f(lhs.green, rhs.green)
		&& eq_f(lhs.blue, rhs.blue);
}

bool rt_math::operator!=(const color& lhs, const color& rhs)
{
	return !(lhs == rhs);
}

rt_math::color rt_math::operator*(const color& lhs, const float rhs)
{
	return color(lhs.red * rhs, lhs.green * rhs, lhs.blue * rhs);
}

/*
 * Hadamard product
 */
rt_math::color rt_math::operator*(const color& lhs, const color& rhs)
{
	return color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue);
}