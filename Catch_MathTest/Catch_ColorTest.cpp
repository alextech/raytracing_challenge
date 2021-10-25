#pragma warning(push, 0)
#include <catch2/catch.hpp>
#pragma warning(pop)
#include "../Math/Math.h"

using namespace rt_math;

SCENARIO("Colors are (red, green, blue) tuples", "[color]")
{
	GIVEN("c <- color(-0.5, 0.4, 1.7)")
	{
		constexpr color c = color(-0.5f, 0.4f, 1.7f);

		REQUIRE(rt_math::eq_f(c.red, -0.5f));
		REQUIRE(rt_math::eq_f(c.green, 0.4f));
		REQUIRE(rt_math::eq_f(c.blue, 1.7f));
	}
}

SCENARIO("Adding colors", "[color]")
{
	GIVEN("c1 <- color(0.9, 0.6, 0.75)")
	{
		constexpr color c1 = color(0.9f, 0.6f, 0.75f);

		AND_GIVEN("c2 <- color(0.7, 0.1, 0.25)")
		{
			constexpr color c2 = color(0.7f, 0.1f, 0.25f);

			REQUIRE(c1 + c2 == color(1.6f, 0.7f, 1.0f));
		}
	}
}

SCENARIO("Subtracting colors", "[color]")
{
	GIVEN("c1 <- color(0.9, 0.6, 0.75)")
	{
		constexpr color c1 = color(0.9f, 0.6f, 0.75f);

		AND_GIVEN("c2 <- color(0.7, 0.1, 0.25)")
		{
			constexpr color c2 = color(0.7f, 0.1f, 0.25f);

			REQUIRE(c1 - c2 == color(0.2f, 0.5f, 0.5f));
		}
	}
}

SCENARIO("Multiplying a color by a scalar", "[color]")
{
	GIVEN("c1 <- color(0.2, 0.3, 0.4)")
	{
		constexpr color c = color(0.2f, 0.3f, 0.4f);

		REQUIRE(c * 2.0f == color(0.4f, 0.6f, 0.8f));
	}
}

SCENARIO("Multiplying colors", "[color]")
{
	GIVEN("c1 <- color(1, 0.2, 0.4)")
	{
		constexpr color c1 = color(1.0f, 0.2f, 0.4f);

		AND_GIVEN("c2 <- color(0.9, 1, 0.1)")
		{
			constexpr color c2 = color(0.9f, 1.0f, 0.1f);

			REQUIRE(c1 * c2 == color(0.9f, 0.2f, 0.04f));
		}
	}
}
