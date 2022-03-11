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

SCENARIO("A scaling matrix applied to a point", "[scaling]")
{
    GIVEN("transform <- scaling(2, 3, 4)")
    {
        const Matrix<4> transform = scaling(2, 3, 4);

        AND_GIVEN("p <- point(-4, 6, 8)")
        {
            tuple p = point(-4, 6, 8);

            REQUIRE(transform * p == point(-8, 18, 32));
        }
    }
}

SCENARIO("A scaling matrix applied to a vector", "[scaling]")
{
    GIVEN("transform <- scaling(2, 3, 4)")
    {
        const Matrix<4> transform = scaling(2, 3, 4);

        AND_GIVEN("v <- vector(-4, 6, 8)")
        {
            const tuple v = vector(-4, 6, 8);

            REQUIRE(transform * v == vector(-8, 18, 32));
        }
    }
}

SCENARIO("Multiplying by the inverse of a scaling matrix", "[scaling]")
{
    GIVEN("transform <- scaling(2, 3, 4)")
    {
        const Matrix<4> transform = scaling(2, 3, 4);

        AND_GIVEN("inv <- inverse(transform)")
        {
            const Matrix<4> inverse = transform.inverse();

            AND_GIVEN("v <- vector(-4, 6, 8)")
            {
                const tuple v = vector(-4, 6, 8);

                REQUIRE(inverse * v == vector(-2, 2, 2));
            }
        }
    }
}

SCENARIO("Reflection is scaling by a negative value", "[scaling]")
{
    GIVEN("transform <- scaling(-1, 1, 1)")
    {
        const Matrix<4> transform = reflection();

        AND_GIVEN("p <- point(2, 3, 4)")
        {
            const tuple p = point(2, 3, 4);

            REQUIRE(transform * p == point(-2, 3, 4));
        }
    }
}
