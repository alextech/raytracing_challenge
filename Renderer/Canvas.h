#pragma once
#include "../Math/Math.h"
#include <memory>
#include <vector>

class Canvas
{
	private:
		
		std::vector<rt_math::color> grid_;
		unsigned int grid_size_;

	public:

		unsigned int const width, height;
		Canvas(unsigned int width, unsigned int height);
        [[nodiscard]] rt_math::color pixel_at(unsigned int const x, unsigned int const y) const;
		void write_pixel(unsigned int const x, unsigned int const y, const rt_math::color color);
		// void write_pixel(float const x, float const y, const rt_math::color color);
        [[nodiscard]] std::vector<rt_math::color>::const_iterator canvas_iterator() const;
};

