#include "BeziersHandlesReversing.hpp"

Instruction * BeziersHandlesReversing::get()
{
	return new BeziersHandlesReversing();
}

/// OK FOR V2

std::vector<VectorImage *> BeziersHandlesReversing::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::vec3 tmp;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				tmp = path.getStartHandle();
				path.setStartHandle(path.getEndHandle());
				path.setEndHandle(tmp);

				path.calculateBounds();
			}

			shape.calculateBounds();
		}
	}

	return vectorImages;
}
