#include "ShapesOrderRandomizer.hpp"

#include "Utils/Utils.hpp"

Instruction * ShapesOrderRandomizer::get()
{
	return new ShapesOrderRandomizer();
}

std::vector<VectorImage *> ShapesOrderRandomizer::execute(const std::vector<VectorImage *> &vectorImages)
{
	vectorImages[0]->applyCursor();

	std::vector<Shape> shapes = vectorImages[0]->getShapes();

	std::random_shuffle(shapes.begin(), shapes.end(), Utils::rand);

	return {new VectorImage(shapes)};
}
