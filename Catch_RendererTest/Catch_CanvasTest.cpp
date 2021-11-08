#define CATCH_CONFIG_MAIN
#pragma warning(push, 0)
#include <catch2/catch.hpp>
#pragma warning(pop)

#include "../Renderer/Canvas.h"

SCENARIO("Creating a canvas", "[canvas]")
{
	GIVEN("c <- canvas(10, 20)")
	{
		const Canvas *c = new Canvas(10, 20);

		REQUIRE(c->width == 10);
		REQUIRE(c->height == 20);

		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 10; ++x)
			{
				REQUIRE(c->pixel_at(x, y) == rt_math::color(0, 0, 0));
			}
		}

	}
}

SCENARIO("Writing pixels to a canvas", "[canvas]")
{
	GIVEN("c <- canvas(10, 20)")
	{
		Canvas* c = new Canvas(10, 20);

		AND_GIVEN("red <- color(1, 0, 0)")
		{
			constexpr rt_math::color red = rt_math::color(1, 0, 0);

			WHEN("write_pixel(c, 2, 3, red)")
			{
				c->write_pixel(2, 3, red);

				REQUIRE(c->pixel_at(2, 3) == red);
			}
		}
	}
}
