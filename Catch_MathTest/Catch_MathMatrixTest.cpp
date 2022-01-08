#pragma warning(push, 0)
#include <catch2/catch.hpp>
#pragma warning(pop)

#include "../Math/Math.h"

using namespace rt_math;

SCENARIO("Constructing and inspecting a 4x4 matrix", "[matrix]")
{

	GIVEN("4x4 matrix M")
	{
		const Matrix M = Matrix<4> {
			1, 2, 3, 4,
			5.5f, 6.5f, 7.5f, 8.5f,
			9, 10, 11, 12,
			13.5, 14.5, 15.5, 16.5
		};

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
		const Matrix M = Matrix<2>{
			-3, 5,
			1, -2
		};

		REQUIRE(eq_f(-3, M.at(0, 0)));
		REQUIRE(eq_f(5, M.at(0, 1)));
		REQUIRE(eq_f(1, M.at(1, 0)));
		REQUIRE(eq_f(-2, M.at(1, 1)));
	}
}

SCENARIO("A 3x3 matrix ought to be representable", "[matrix]")
{
	GIVEN("3x3 matrix M")
	{
		const Matrix M = Matrix<3>{
			-3, 5, 0,
			1, -2, -7,
			0, 1, 1
		};

		REQUIRE(eq_f(-3, M.at(0, 0)));
		REQUIRE(eq_f(-2, M.at(1, 1)));
		REQUIRE(eq_f(1, M.at(2, 2)));
	}
}

SCENARIO("Matrix equality with identical matrices", "[matrix]")
{
	GIVEN("Matrix A and matrix B")
	{
		const Matrix<4> A = Matrix<4>{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		const Matrix<4> B = Matrix<4>{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		REQUIRE(A == B);
	}
}

SCENARIO("Matrix equality with different matrices", "[matrix]")
{
	GIVEN("Matrix A and matrix B")
	{
		const Matrix A = Matrix<4>{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		const Matrix B = Matrix<4>{
			2, 3, 4, 5,
			6, 7, 8, 9,
			8, 7, 6, 5,
			4, 3, 2, 1
		};

		REQUIRE(A != B);
	}
}

SCENARIO("Multiplying two matrices", "[matrix]")
{
	GIVEN("Matrix A and matrix B")
	{
		const Matrix A = Matrix<4>{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		};

		const Matrix B = Matrix<4>{
			-2, 1, 2, 3,
			3,  2, 1, -1,
			4,  3, 6, 5,
			1,  2, 7, 8
		};

		REQUIRE(A * B == Matrix<4>{
			20, 22, 50, 48,
			44, 54, 114, 108,
			40, 58, 110, 102,
			16, 26, 46, 42
		});
	}
}

SCENARIO("A matrix multiplied by a tuple", "[matrix]")
{
    GIVEN("Matrix A")
    {
		const Matrix A = Matrix<4>{
			1, 2, 3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1
		};

		AND_GIVEN("b <- tuple(1, 2, 3, 1)")
		{
			constexpr tuple b = tuple(1, 2, 3, 1);

			REQUIRE(A * b == tuple(18, 24, 33, 1));
		}
    }
}

SCENARIO("Multiplying a matrix by identity matrix", "[matrix]")
{
    GIVEN("Matrix A")
    {
		const Matrix A = Matrix<4>{
			0, 1,  2,  4,
			1, 2,  4,  8,
			2, 4,  8,  6,
			4, 8, 16, 32
		};

		REQUIRE(A * Matrix<4>::identity_matrix() == A);
    }
}

SCENARIO("Multiplying the identity matrix by a tuple", "[matrix]")
{
    GIVEN("a <- tuple(1, 2, 3, 4)")
    {
		constexpr tuple a = tuple(1, 2, 3, 4);

		REQUIRE(Matrix<4>::identity_matrix() * a == a);
    }
}
