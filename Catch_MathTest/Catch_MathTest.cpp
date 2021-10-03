#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "../Math/Math.h"

using namespace rt_math;

SCENARIO("A tuple with w=1.0 is a point", "[coordinates]") {

    GIVEN("a tuple") {

        tuple *a = new tuple(4.3f, -4.2f, 3.1f, 1.0f);

        THEN("Can access point coordinates")
        {
            REQUIRE(eq_f(a->x, 4.3f));
            REQUIRE(eq_f(a->y, -4.2f));
            REQUIRE(eq_f(a->z, 3.1f));
            REQUIRE(eq_f(a->w, 1.0f));

	        AND_THEN("a is a point")
	        {
                REQUIRE(a->IsPoint());
	        }

            AND_THEN("a is not a vector")
	        {
                REQUIRE_FALSE(a->IsVector());
	        }
        }

        
    }
}

SCENARIO("point() creates tuples with w = 1", "[coordinates]")
{
	GIVEN("p <- point(4, -4, 3")
	{
		const tuple p = point(4, -4, 3);

		THEN("p = tuple(4, -4, 3, 1")
		{
            REQUIRE(p == tuple(4, -4, 3, 1));
		}
	}
}

SCENARIO("vector() creates tuples with w = 0", "[coordinates]")
{
    GIVEN("p <- vector(4, -4, 3")
    {
	    const tuple p = vector(4, -4, 3);

        THEN("p = tuple(4, -4, 3, 0)")
        {
            REQUIRE(p == tuple(4, -4, 3, 0));
        }
    }
}

/*
 * In geometry, vector + point = vector; vector + vector = vector; point + point = doesnt make sense
 */
SCENARIO("Adding two tuples", "[coordinates]")
{
	GIVEN("a1 <- tuple(3, -2, 5, 1)")
	{
		const tuple a1 = tuple(3, -2, 5, 1);

		AND_GIVEN("a2 <- tuple(-2, 3, 1, 0)")
		{
			const tuple a2 = tuple(-2, 3, 1, 0);

			THEN("a1 + a2 = tuple(1, 1, 6, 1)")
			{
				const tuple sum = a1 + a2;

				REQUIRE(sum == tuple(1, 1, 6, 1));
			}
		}
	}
}

/*
 * In geometry, point - point = vector. Direction vector how to get from first point to second.
 */
SCENARIO("Subtracting two points", "[coordinates]")
{
	GIVEN("p1 <- point(3, 2, 1)")
	{
		const tuple p1 = point(3, 2, 1);

		AND_GIVEN("p2 <- point(5, 6, 7)")
		{
			const tuple p2 = point(5, 6, 7);

			THEN("p1 - p2 = vector(-2, -4, -6)")
			{
				const tuple v = p1 - p2;

				REQUIRE(v == vector(-2, -4, -6));
			}
		}
	}
}

/*
 * In geometry, point - vector = point. New point using direction vector from original point.
 */
SCENARIO("Subtracting a vector from a point", "[coordinates]")
{
	GIVEN("p <- point(3, 2, 1)")
	{
		const tuple p = point(3, 2, 1);

		AND_GIVEN("v <- vector(5, 6, 7)")
		{
			const tuple v = vector(5, 6, 7);

			REQUIRE(p - v == point(-2, -4, -6));
		}
	}
}

/*
 * In geometry, vector - vector = vector. New vector as change of direction between two.
 */
SCENARIO("Subtracting two vectors", "[coordinates]")
{
	GIVEN("v1 <- vector(3, 2, 1)")
	{
		const tuple v1 = vector(3, 2, 1);

		AND_GIVEN("v2 <- vector(5, 6, 7)")
		{
			const tuple v2 = vector(5, 6, 7);

			REQUIRE(v1 - v2 == vector(-2, -4, -6));
		}
	}
}

SCENARIO("Subtracting a vector from a zero vector", "[coordinates]")
{
	GIVEN("zero <- vector(0, 0, 0)")
	{
		const tuple zero = vector(0, 0, 0);

		AND_GIVEN("v <- vector(1, -2, 3")
		{
			const tuple v = vector(1, -2, 3);

			REQUIRE(zero - v == vector(-1, 2, -3));
		}
	}
}

SCENARIO("Negating a tuple", "[coordinates]")
{
	GIVEN("a <- tuple(1, -2, 3, -4")
	{
		const tuple a = tuple(1, -2, 3, -4);

		REQUIRE(-a == tuple(-1, 2, -3, 4));
	}
}
