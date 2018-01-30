#include "PathsOrderInvert.hpp"
#include <algorithm>

Instruction * PathsOrderInvert::get()
{
	return new PathsOrderInvert();
}

std::vector<VectorImage *> PathsOrderInvert::execute(const std::vector<VectorImage *> &vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	std::reverse(paths.begin(), paths.end());

	Shape shape;

	for(Bezier path : paths)
	{
		shape << path;
	}

	return {new VectorImage(shape)};
}