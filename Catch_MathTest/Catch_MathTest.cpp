#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "../Math/Math.h"

using namespace rt_math;

SCENARIO("A tuple with w=1.0 is a point", "[geometry]") {

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

SCENARIO("point() creates tuples with w = 1", "[geometry]")
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

SCENARIO("vector() creates tuples with w = 0", "[geometry]")
{
    GIVEN("p <- vector(4, -4, 3")
    {
	    const tuple p = vector(4, -4, 3);

        THEN("p = tuple(4, -4, 3, 0")
        {
            REQUIRE(p == tuple(4, -4, 3, 0));
        }
    }
}
