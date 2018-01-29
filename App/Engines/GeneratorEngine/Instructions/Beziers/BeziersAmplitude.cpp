#include "BeziersAmplitude.hpp"

Instruction * BeziersAmplitude::get()
{
	return new BeziersAmplitude();
}

std::vector<VectorImage *> BeziersAmplitude::execute(const std::vector<VectorImage *> &vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	Shape shape;

	for(Bezier path : paths)
	{
		path.setStartHandle(path.getStartHandle() * 2);
		path.setEndHandle(path.getEndHandle() * 2);
		shape << path;
	}

	return {new VectorImage(vectorImages[0]->getWidth(), vectorImages[0]->getHeight(), shape)};
}
