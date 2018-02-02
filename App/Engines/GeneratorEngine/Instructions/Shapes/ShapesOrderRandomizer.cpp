#include "ShapesOrderRandomizer.hpp"

#include "Utils/Utils.hpp"

Instruction * ShapesOrderRandomizer::get()
{
	return new ShapesOrderRandomizer();
}

/// OK FOR V2

std::vector<VectorImage *> ShapesOrderRandomizer::execute(std::vector<VectorImage *> &vectorImages)
{
	for(VectorImage * vImage : vectorImages)
	{
		std::random_shuffle(vImage->getShapes()->begin(), vImage->getShapes()->end(), Utils::rand);
	}

	return vectorImages;
}
