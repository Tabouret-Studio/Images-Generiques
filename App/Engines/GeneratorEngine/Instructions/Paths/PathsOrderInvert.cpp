#include "PathsOrderInvert.hpp"
#include <algorithm>

Instruction * PathsOrderInvert::get()
{
	return new PathsOrderInvert();
}

/// OK FOR V2

std::vector<VectorImage *> PathsOrderInvert::execute(std::vector<VectorImage *> &vectorImages)
{
	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			std::reverse(shape.getPaths()->begin(), shape.getPaths()->end());
		}
	}

	return vectorImages;
}
