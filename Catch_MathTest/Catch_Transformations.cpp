#include <catch2/catch.hpp>
#include "../Math/Math.h"

using namespace rt_math;

SCENARIO("Multiplying by a translation matrix", "[translation]")
{
    GIVEN("transform <- translation(5, -3, 2)")
    {
        const Matrix<4> transform = translation(5, -3, 2);

        AND_GIVEN("p <- point(-3, 4, 5)")
        {
            const tuple p = point(-3, 4, 5);

            REQUIRE(transform * p == point(2, 1, 7));
        }
    }
}

// moves point backward
SCENARIO("Multiplying by the inverse of a translation matrix", "[translation]")
{
    GIVEN("transform <- translation(5, -3, 2)")
    {
        const Matrix<4> transform = translation(5, -3, 2);

        AND_GIVEN("inv <- inverse(transform)")
        {
            const Matrix<4> inverse = transform.inverse();

            AND_GIVEN("p <- point(-3, 4, 5)")
            {
                const tuple p = point(-3, 4, 5);

                REQUIRE(inverse * p == point(-8, 7, 3));
            }
        }
    }
}

SCENARIO("Translation does not affect vectors", "[translation]")
{
    GIVEN("transform <- translation(5, -3, 2)")
    {
        const Matrix<4> transform = translation(5, -3, 2);

        AND_GIVEN("vector <- vector(-3, 4, 5)")
        {
            const tuple v = vector(-3, 4, 5);

            REQUIRE(transform * v == v);
        }
    }
}


