#include <catch2/catch.hpp>
#include "../Math/Math.h"
#include "../Math/Geometry.h"

using namespace rt_math;

SCENARIO("Creating and querying a ray")
{
    GIVEN("origin and direction")
    {
        const tuple origin    = point(1, 2, 3);
        const tuple direction = vector(4, 5, 6);

        WHEN("r <- ray(origin, direction)")
        {
            const Ray r = Ray(origin, direction);

            REQUIRE(origin == r.origin);
            REQUIRE(direction == r.direction);
        }
    }
}

SCENARIO("Computing a point from a distance")
{
    GIVEN("ray")
    {
        const Ray ray = Ray(point(2, 3, 4), vector(1, 0, 0));

        REQUIRE(position(ray, 0) == point(2, 3, 4));
        REQUIRE(position(ray, 1) == point(3, 3, 4));
        REQUIRE(position(ray, -1) == point(1, 3, 4));
        REQUIRE(position(ray, 2.5f) == point(4.5f, 3, 4));
    }
}
