#include "Math.h"

rt_math::M_4x4::M_4x4(float r1_c1, float r1_c2, float r1_c3, float r1_c4, float r2_c1, float r2_c2, float r2_c3,
	float r2_c4, float r3_c1, float r3_c2, float r3_c3, float r3_c4, float r4_c1, float r4_c2, float r4_c3, float r4_c4)
{
	_matrix.reserve(16);
	_matrix.push_back(r1_c1);
	_matrix.push_back(r1_c2);
	_matrix.push_back(r1_c3);
	_matrix.push_back(r1_c4);
	_matrix.push_back(r2_c1);
	_matrix.push_back(r2_c2);
	_matrix.push_back(r2_c3);
	_matrix.push_back(r2_c4);
	_matrix.push_back(r3_c1);
	_matrix.push_back(r3_c2);
	_matrix.push_back(r3_c3);
	_matrix.push_back(r3_c4);
	_matrix.push_back(r4_c1);
	_matrix.push_back(r4_c2);
	_matrix.push_back(r4_c3);
	_matrix.push_back(r4_c4);
}

float rt_math::M_4x4::at(int row, int column)
{
	int index = row * 4 + column;
	return _matrix[index];
}
