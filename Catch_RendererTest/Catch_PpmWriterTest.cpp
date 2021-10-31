#pragma warning(push, 0)
#include <catch2/catch.hpp>
#pragma warning(pop)

#include <fstream>
#include <sstream>
#include "../Renderer/Canvas.h"
#include "../Renderer/PpmWriter.h"
#include "../Math/Math.h"

using namespace rt_math;

class PpmWriter;
const std::string tmpFileName = "tst_output.ppm";
std::string read_lines(const int start, const int end)
{
	std::stringstream outputStream;

	std::ifstream outputFile(tmpFileName);
	if (outputFile.is_open())
	{
		int currentLine = 1;
		std::string lineContent;
		while (std::getline(outputFile, lineContent))
		{
			if (currentLine >= start && currentLine <= end)
			{
				outputStream << lineContent;
				if (currentLine != end)
				{
					outputStream << std::endl;
				}
			}

			currentLine++;
		}
		outputFile.close();
	}
	else outputStream << "Unable to open output file for comparison.";

	return outputStream.str();
}


SCENARIO("Constructing the PPM header", "[ppm]")
{
	GIVEN("c <- canvas(5, 3)")
	{
		Canvas *c = new Canvas(5, 3);

		WHEN("ppm <- canvas_to_ppm(c)")
		{
			PpmWriter* writer = new PpmWriter(tmpFileName);
			writer->canvas_to_ppm(c);

			REQUIRE(read_lines(1, 3) == 
R"(P3
5 3
255)");
		}
	}
}

SCENARIO("Constructing the PPM pixel data", "[ppm]")
{
	GIVEN("c <- canvas(5, 3)")
	{
		Canvas *c = new Canvas(5, 3);

		AND_GIVEN("c1 <- color(1.5, 0, 0)")
		{
			color c1 = color(1.5, 0, 0);

			AND_GIVEN("c2 <- color(0, 0.5, 0)")
			{

				color c2 = color(0, 0.5, 0);

				AND_GIVEN("c3 <- color(-0.5, 0, 1")
				{

					color c3 = color(-0.5, 0, 1);

					WHEN("write_pixel(c, 0, 0, c1)")
					{

						c->write_pixel(0, 0, c1);

						AND_WHEN("write_pixel(c, 2, 1, c2)")
						{

							c->write_pixel(2, 1, c2);

							AND_WHEN("write_pixel(c, 4, 2, c3)")
							{

								c->write_pixel(4, 2, c3);

								AND_WHEN("ppm <- canvas_to_ppm(c)")
								{

									PpmWriter* writer = new PpmWriter(tmpFileName);
									writer->canvas_to_ppm(c);

									REQUIRE(read_lines(4, 6) ==
R"(255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 255)");
								}
							}
						}
					}
				}
			}
		}
	}
}
