#include "ShapesOrderInvert.hpp"
#include <algorithm>

Instruction * ShapesOrderInvert::get()
{
	return new ShapesOrderInvert();
}

std::vector<VectorImage *> ShapesOrderInvert::execute(const std::vector<VectorImage *> &vectorImages)
{
	vectorImages[0]->applyCursor();
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	std::reverse(paths.begin(), paths.end());

	Shape shape;

	for(Bezier path : paths)
	{
		shape << path;
	}

	return {new VectorImage(shape)};
}
