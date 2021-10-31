#include "pch.h"
#include "PpmWriter.h"

#include <iostream>
#include <fstream>

void PpmWriter::canvas_to_ppm(const Canvas* canvas) const
{
	std::ofstream output(this->outputFileName_);

	// if(output.is_open())
	// {
	output
		<< "P3" << std::endl
		<< canvas->width << " " << canvas->height << std::endl
		<< "255";

	output.close();
	// } 
}
