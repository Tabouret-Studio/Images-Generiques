#include "ShapesOrderInvert.hpp"
#include <algorithm>

Instruction * ShapesOrderInvert::get()
{
	return new ShapesOrderInvert();
}

/// OK FOR V2

std::vector<VectorImage *> ShapesOrderInvert::execute(std::vector<VectorImage *> &vectorImages)
{
	for(VectorImage * vImage : vectorImages)
	{
		std::reverse(vImage->getShapes()->begin(), vImage->getShapes()->end());
	}

	return vectorImages;
}
