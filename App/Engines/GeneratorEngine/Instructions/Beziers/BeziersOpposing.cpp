#include "BeziersOpposing.hpp"

Instruction * BeziersOpposing::get()
{
	return new BeziersOpposing();
}

std::vector<VectorImage *> BeziersOpposing::execute(const std::vector<VectorImage *> &vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	Shape shape;

	for(Bezier path : paths)
	{
		path.setStartHandle(2 * path.getStartPoint() - path.getStartHandle());
		path.setEndHandle(2 * path.getEndPoint() - path.getEndHandle());
		shape << path;
	}

	return {new VectorImage(vectorImages[0]->getWidth(), vectorImages[0]->getHeight(), shape)};
}
