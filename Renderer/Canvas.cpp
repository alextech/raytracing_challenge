#include "pch.h"
#include "Canvas.h"
#include <cassert>

Canvas::Canvas(unsigned int const width, unsigned int const height) : width(width), height(height)
{
	unsigned int const gridSize = width * height;

	this->grid_ = std::make_unique<rt_math::color[]>(gridSize);

	for (unsigned int i = 0; i < gridSize; ++i)
	{
		this->grid_[i] = rt_math::color(0, 0, 0);
	}
	this->grid_size_ = gridSize;
}

rt_math::color Canvas::pixel_at(unsigned int const x, unsigned int const y) const
{
	unsigned int const offset = x * y + x;
	assert(offset < this->grid_size_);

	return this->grid_[offset];
}

void Canvas::write_pixel(unsigned const x, unsigned const y, const rt_math::color &color) const
{
	unsigned int const offset = x * y + x;
	assert(offset < this->grid_size_);

	this->grid_[offset] = color;
}


