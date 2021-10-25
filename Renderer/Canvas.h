#pragma once
#include "../Math/Math.h"
#include <memory>

class Canvas
{
	private:
		
		std::unique_ptr<rt_math::color[]> grid_;
		unsigned int grid_size_;

	public:

		unsigned int const width, height;
		Canvas(unsigned int width, unsigned int height);
		rt_math::color pixel_at(unsigned int const x, unsigned int const y) const;
		void write_pixel(unsigned int const x, unsigned int const y, const rt_math::color &color) const;
};

