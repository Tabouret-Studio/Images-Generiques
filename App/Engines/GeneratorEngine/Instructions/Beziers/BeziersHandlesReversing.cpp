#include "BeziersHandlesReversing.hpp"

Instruction * BeziersHandlesReversing::get()
{
	return new BeziersHandlesReversing();
}

std::vector<VectorImage *> BeziersHandlesReversing::execute(const std::vector<VectorImage *> &vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	Shape shape;
	glm::vec3 tmp;

	for(Bezier path : paths)
	{
		tmp = path.getStartHandle();
		path.setStartHandle(path.getEndHandle());
		path.setEndHandle(tmp);
		shape << path;
	}

	return {new VectorImage(vectorImages[0]->getWidth(), vectorImages[0]->getHeight(), shape)};
}
