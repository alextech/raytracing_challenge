#include "pch.h"
#include "Canvas.h"
#include <cassert>

Canvas::Canvas(unsigned int const width, unsigned int const height) : width(width), height(height)
{
	unsigned int const grid_size = width * height;
	this->grid_.reserve(grid_size);

	for (unsigned int i = 0; i < grid_size; ++i)
	{
		this->grid_.push_back(rt_math::color(0, 0, 0));
	}
	this->grid_size_ = grid_size;
}

rt_math::color Canvas::pixel_at(unsigned int const x, unsigned int const y) const
{
	unsigned int const offset = this->width * y + x;
	assert(offset < this->grid_size_);

	return this->grid_[offset];
}

void Canvas::write_pixel(unsigned const x, unsigned const y, const rt_math::color color)
{
	unsigned int const offset = this->width * y + x;
	assert(offset < this->grid_size_);


	this->grid_[offset] = color;
}

std::vector<rt_math::color>::const_iterator Canvas::canvas_iterator() const
{
	return this->grid_.begin();
}
