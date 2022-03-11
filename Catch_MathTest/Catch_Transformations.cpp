#include <catch2/catch.hpp>
#include <numbers>
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

SCENARIO("Rotating a point around the x axis", "[rotation]")
{
    GIVEN("p <- point(0, 1, 0)")
    {
        tuple p = point(0, 1, 0);

        AND_GIVEN("half_quarter <- rotation_x(pi/4)")
        {
            const Matrix<4> half_quarter = rotation_x(std::numbers::pi_v<float> / 4.0f);

            AND_GIVEN("full_quarter <- rotation_x(pi/2)")
            {
                const Matrix<4> full_quarter = rotation_x(std::numbers::pi_v<float> / 2.0f);

                REQUIRE(half_quarter * p == point(0, sqrt(2.0f) / 2.0f, sqrt(2.0f) / 2.0f));
                REQUIRE(full_quarter * p == point(0, 0, 1));
            }
        }
    }
}

SCENARIO("The inverse of an x-rotation rotates in the opposite direction", "[rotation]")
{
    GIVEN("p <- point(0, 1, 0)")
    {
        const tuple p = point(0, 1, 0);

        AND_GIVEN("half_quarter <- rotation_x(pi/4)")
        {
            const Matrix<4> half_quarter = rotation_x(std::numbers::pi_v<float> / 4.0f);

            AND_GIVEN("inv <- inverse(half_quarter)")
            {
                const Matrix<4> inv = half_quarter.inverse();

                REQUIRE(inv * p == point(0, sqrt(2.0f)/2.0f, -sqrt(2.0f)/2.0f));
            }
        }
    }
}

SCENARIO("Rotating a point around the y axis", "[rotation]")
{
    GIVEN("p <- point(0, 0, 1)")
    {
        const tuple p = point(0, 0, 1);
        const Matrix<4> half_quarter = rotation_y(std::numbers::pi_v<float> / 4.0f);
        const Matrix<4> full_quarter = rotation_y(std::numbers::pi_v<float> / 2.0f);

        REQUIRE(half_quarter * p == point(sqrt(2.0f)/2.0f, 0.0f, sqrt(2.0f)/2.0f));
        REQUIRE(full_quarter * p == point(1.0f, 0, 0));
    }
}

SCENARIO("Rotating a point around the z axis", "[rotation]")
{
    GIVEN("p <- point(0, 1, 0)")
    {
        const tuple p = point(0, 1, 0);
        const Matrix<4> half_quarter = rotation_z(std::numbers::pi_v<float> / 4.0f);
        const Matrix<4> full_quarter = rotation_z(std::numbers::pi_v<float> / 2.0f);

        REQUIRE(half_quarter * p == point(-sqrt(2.0f)/2.0f, sqrt(2.0f)/2.0f, 0));
        REQUIRE(full_quarter * p == point(-1.0f, 0, 0));
    }
}
