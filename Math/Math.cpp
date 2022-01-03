#include "Math.h"

rt_math::color operator*(const rt_math::color lhs, const float rhs)
{
	return rt_math::color(lhs.red * rhs, lhs.green * rhs, lhs.blue * rhs);
}

template <typename T>
rt_math::M_4x4<T>::M_4x4(T r1_c1, T r1_c2, T r1_c3, T r1_c4, T r2_c1, T r2_c2, T r2_c3,
	T r2_c4, T r3_c1, T r3_c2, T r3_c3, T r3_c4, T r4_c1, T r4_c2, T r4_c3, T r4_c4)
{
	matrix_.reserve(16);
	matrix_.push_back(r1_c1);
	matrix_.push_back(r1_c2);
	matrix_.push_back(r1_c3);
	matrix_.push_back(r1_c4);
	matrix_.push_back(r2_c1);
	matrix_.push_back(r2_c2);
	matrix_.push_back(r2_c3);
	matrix_.push_back(r2_c4);
	matrix_.push_back(r3_c1);
	matrix_.push_back(r3_c2);
	matrix_.push_back(r3_c3);
	matrix_.push_back(r3_c4);
	matrix_.push_back(r4_c1);
	matrix_.push_back(r4_c2);
	matrix_.push_back(r4_c3);
	matrix_.push_back(r4_c4);
}

template <typename T>
T rt_math::M_4x4<T>::at(const int row, const int column) const
{
	int index = row * 4 + column;
	return matrix_[index];
}

template <typename T>
rt_math::M_2x2<T>::M_2x2(const T r1_c1, const T r1_c2, const T r2_c1, const T r2_c2)
{
	matrix_.reserve(4);
	matrix_.push_back(r1_c1);
	matrix_.push_back(r1_c2);
	matrix_.push_back(r2_c1);
	matrix_.push_back(r2_c2);
}

template <typename T>
T rt_math::M_2x2<T>::at(const int row, const int column) const
{
	int index = row * 2 + column;
	return matrix_[index];
}

template <typename T>
rt_math::M_3x3<T>::M_3x3(const T r1_c1, const T r1_c2, const T r1_c3, const T r2_c1, const T r2_c2, const T r2_c3,
	const T r3_c1, const T r3_c2, const T r3_c3)
{
	matrix_.reserve(9);
	matrix_.push_back(r1_c1);
	matrix_.push_back(r1_c2);
	matrix_.push_back(r1_c3);
	matrix_.push_back(r2_c1);
	matrix_.push_back(r2_c2);
	matrix_.push_back(r2_c3);
	matrix_.push_back(r3_c1);
	matrix_.push_back(r3_c2);
	matrix_.push_back(r3_c3);
}

template <typename T>
T rt_math::M_3x3<T>::at(const int row, const int column) const
{
	int index = row * 3 + column;
	return matrix_[index];
}

template class rt_math::M_4x4<float>;
template class rt_math::M_4x4<int>;
template class rt_math::M_2x2<float>;
template class rt_math::M_2x2<int>;
template class rt_math::M_3x3<float>;
template class rt_math::M_3x3<int>;
