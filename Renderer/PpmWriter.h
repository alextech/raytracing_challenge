#pragma once

#include <string>
#include <utility>

#include "Canvas.h"

class PpmWriter
{

private:
	std::string outputFileName_;

public:
	PpmWriter(std::string outputFileName) : outputFileName_(std::move(outputFileName)) {}
	void canvas_to_ppm(const Canvas* canvas) const;
};

