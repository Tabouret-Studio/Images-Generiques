#include "BeziersLinearAlizer.hpp"

Instruction * BeziersLinearAlizer::get()
{
	return new BeziersLinearAlizer();
}

std::vector<VectorImage *> BeziersLinearAlizer::execute(const std::vector<VectorImage *> &vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	Shape shape;

	for(Bezier path : paths)
	{
		path.setStartHandle(path.getStartPoint());
		path.setEndHandle(path.getEndPoint());
		shape << path;
	}

	return {new VectorImage(vectorImages[0]->getWidth(), vectorImages[0]->getHeight(), shape)};
}
