#pragma warning(push, 0)
#include <catch2/catch.hpp>
#pragma warning(pop)

#include "../Math/Math.h"

using namespace rt_math;

SCENARIO("Constructing and inspecting a 4x4 matrix", "[matrix]")
{

	GIVEN("4x4 matrix M")
	{

		M_4x4 M = M_4x4(
			1, 2, 3, 4,
			5.5, 6.5, 7.5, 8.5,
			9, 10, 11, 12,
			13.5, 14.5, 15.5, 16.5
		);

		REQUIRE(1.0f == M.at(0, 0));
		REQUIRE(4.0f == M.at(0, 3));
		REQUIRE(5.5f == M.at(1, 0));
		REQUIRE(7.5f == M.at(1, 2));
		REQUIRE(11.0f == M.at(2, 2));
		REQUIRE(13.5f == M.at(3, 0));
		REQUIRE(15.5f == M.at(3, 2));
	}
}

SCENARIO("A 2x2 matrix ought to be representable", "[matrix]")
{
	GIVEN("2x2 matrix M")
	{
		M_2x2 M = M_2x2(
			-3, 5,
			1, -2
		);

		REQUIRE(-3 == M.at(0, 0));
		REQUIRE(5 == M.at(0, 1));
		REQUIRE(1 == M.at(1, 0));
		REQUIRE(-2 == M.at(1, 1));
	}
}

SCENARIO("A 3x3 matrix ought to be representable", "[matrix]")
{
	GIVEN("3x3 matrix M")
	{
		M_3x3 M = M_3x3(
			-3, 5, 0,
			1, -2, -7,
			0, 1, 1
		);

		REQUIRE(-3 == M.at(0, 0));
		REQUIRE(-2 == M.at(1, 1));
		REQUIRE(1 == M.at(2, 2));
	}
}

SCENARIO("Matrix equality with identical matrices", "[matrix]")
{
	GIVEN("Matrix A and matrix B")
	{
		M_4x4 A = M_4x4(
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		);

		M_4x4 B = M_4x4(
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		);

		REQUIRE(A == B);
	}
}

SCENARIO("Matrix equality with different matrices", "[matrix]")
{
	GIVEN("Matrix A and matrix B")
	{
		M_4x4 A = M_4x4(
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
			);

		M_4x4 B = M_4x4(
			2, 3, 4, 5,
			6, 7, 8, 9,
			8, 7, 6, 5,
			4, 3, 2, 1
			);

		REQUIRE(A != B);
	}
}

SCENARIO("Multiplying two matrices", "[matrix]")
{
	GIVEN("Matrix A and matrix B")
	{
		M_4x4 A = M_4x4(
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
			);

		M_4x4 B = M_4x4(
			-2, 1, 2, 3,
			3,  2, 1, -1,
			4,  3, 6, 5,
			1,  2, 7, 8
			);

		REQUIRE(A * B == M_4x4(
			20, 22,  50,  48,
			44, 54, 114, 108,
			40, 58, 110, 102,
			16, 26,  46,  42
		));
	}
}
