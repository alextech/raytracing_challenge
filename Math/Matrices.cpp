#include "Math.h"

// ======================================
//             MATRIX DEFINITIONS
// ======================================


rt_math::M_4x4::M_4x4(
	const float r1_c1, const float r1_c2, const float r1_c3, const float r1_c4, 
	const float r2_c1, const float r2_c2, const float r2_c3, const float r2_c4, 
	const float r3_c1, const float r3_c2, const float r3_c3, const float r3_c4, 
	const float r4_c1, const float r4_c2, const float r4_c3, const float r4_c4)
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

float rt_math::M_4x4::at(const int row, const int column) const
{
	const int index = row * 4 + column;
	return matrix_[index];
}

rt_math::M_2x2::M_2x2(
	const float r1_c1, const float r1_c2, 
	const float r2_c1, const float r2_c2)
{
	matrix_.reserve(4);
	matrix_.push_back(r1_c1);
	matrix_.push_back(r1_c2);
	matrix_.push_back(r2_c1);
	matrix_.push_back(r2_c2);
}

float rt_math::M_2x2::at(const int row, const int column) const
{
	const int index = row * 2 + column;
	return matrix_[index];
}

rt_math::M_3x3::M_3x3(
	const float r1_c1, const float r1_c2, const float r1_c3, 
	const float r2_c1, const float r2_c2, const float r2_c3,
	const float r3_c1, const float r3_c2, const float r3_c3)
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

float rt_math::M_3x3::at(const int row, const int column) const
{
	const int index = row * 3 + column;
	return matrix_[index];
}


// =======================================
//            OPERATIONS WITH MATRICES
// =======================================
rt_math::M_4x4 rt_math::M_4x4::operator*(const rt_math::M_4x4 &rhs) const
{
	std::vector<float> tmpM;
	tmpM.reserve(16);
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			float sum =
				at(r, 0) * rhs.at(0, c) +
				at(r, 1) * rhs.at(1, c) +
				at(r, 2) * rhs.at(2, c) +
				at(r, 3) * rhs.at(3, c);

			tmpM.push_back(sum);
		}
	}

	// M_4x4(tmpM)
	// [modernize-return-braced-init-list] produces warning
	// Avoid repeating the return type from the declaration;
	//    use braced initializer list instead

	return tmpM;
}

bool rt_math::operator==(const M_4x4 &lhs, const M_4x4 &rhs)
{
	return std::equal(
		lhs.matrix_.begin(), lhs.matrix_.end(),
		rhs.matrix_.begin(),
		[](const float& left, const float& right)
		{
			return eq(left, right);
		}
	);
}
