#include "pch.h"
#include "PpmWriter.h"

#include <fstream>

void PpmWriter::canvas_to_ppm(const Canvas* canvas) const
{
	std::ofstream output(this->outputFileName_);

	// if(output.is_open())
	// {
	output
		<< "P3" << std::endl
		<< canvas->width << " " << canvas->height << std::endl
		<< "255" << std::endl;

	std::vector<rt_math::color>::const_iterator it = canvas->canvas_iterator();

	const unsigned int last_coll_offset = canvas->width - 1;
	unsigned int char_counter = 0;
	for(unsigned int y = 0; y < canvas->height; ++y)
	{
		for (unsigned int x = 0; x < canvas->width; ++x)
		{
			const unsigned int red   = it->red   > 0 ? static_cast<unsigned int>(round(it->red   * 255.0f)) : 0;
			const unsigned int green = it->green > 0 ? static_cast<unsigned int>(round(it->green * 255.0f)) : 0;
			const unsigned int blue  = it->blue  > 0 ? static_cast<unsigned int>(round(it->blue  * 255.0f)) : 0;

			output << (red > 255 ? 255 : red);
			char_counter = char_counter + 3;
			if (char_counter + 7 > 70)
			{
				output << std::endl;
				char_counter = 0;
			} else
			{
				output << " ";
				char_counter = char_counter + 1;
			}

			
			output << (green > 255 ? 255 : green);
			char_counter = char_counter + 3;
			if (char_counter + 7 > 70)
			{
				output << std::endl;
				char_counter = 0;
			}
			else
			{
				output << " ";
				char_counter = char_counter + 1;
			}


			output << (blue > 255 ? 255 : blue);
			char_counter = char_counter + 3;
			if (x == last_coll_offset || (char_counter + 7 > 70))
			{
				output << std::endl;
				char_counter = 0;
			}
			else
			{
				output << " ";
				char_counter = char_counter + 1;
			}

			std::advance(it, 1);
		}
	}
	

	output.close();
	// } 
}
