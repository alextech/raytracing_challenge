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

SCENARIO("A ray intersects a sphere at two points")
{
    GIVEN("sphere and ray")
    {
        const Ray ray = Ray(point(0, 0, -5), vector(0, 0, 1));
        const Sphere sphere = Sphere();

        WHEN("xs <- intersects(sphere, ray)")
        {
            const std::vector<float> xs = sphere.intersects(ray);

            REQUIRE(xs.size() == 2);
            REQUIRE(xs[0] == 4.0f);
            REQUIRE(xs[1] == 6.0f);
        }
    }
}

SCENARIO("A ray intersects a sphere at a tangent")
{
    GIVEN("sphere and ray")
    {
        const Ray ray = Ray(point(0, 1, -5), vector(0, 0, 1));
        const Sphere sphere = Sphere();

        WHEN("xs <- intersects(sphere, ray)")
        {
            const std::vector<float> xs = sphere.intersects(ray);
            REQUIRE(xs.size() == 2);
            REQUIRE(xs[0] == 5.0f);
            REQUIRE(xs[1] == 5.0f);
        }
    }
}

SCENARIO("A ray misses a sphere")
{
    GIVEN("sphere and ray")
    {
        const Ray ray = Ray(point(0, 2, -5), vector(0, 0, 1));
        const Sphere sphere = Sphere();

        WHEN("xs <- intersects(sphere, ray)")
        {
            const std::vector<float> xs = sphere.intersects(ray);

            REQUIRE(xs.empty());
        }
    }
}

SCENARIO("A ray originates inside a sphere")
{
    GIVEN("sphere and ray")
    {
        const Ray ray = Ray(point(0, 0, 0), vector(0, 0, 1));
        const Sphere sphere = Sphere();

        WHEN("xs <- intersects(sphere, ray))")
        {
            const std::vector<float> xs = sphere.intersects(ray);

            REQUIRE(xs.size() == 2);
            REQUIRE(eq_f(xs[0], -1.0f));
            REQUIRE(eq_f(xs[1], 1.0f));
        }
    }
}

SCENARIO("A sphere is behind a ray")
{
    GIVEN("sphere and ray")
    {
        const Ray ray = Ray(point(0, 0, 5), vector(0, 0, 1));
        const Sphere sphere = Sphere();

        WHEN("xs <- intersects(sphere, ray)")
        {
            const std::vector<float> xs = sphere.intersects(ray);

            REQUIRE(xs.size() == 2);
            REQUIRE(eq_f(xs[0], -6.0f));
            REQUIRE(eq_f(xs[1], -4.0f));
        }
    }
}
