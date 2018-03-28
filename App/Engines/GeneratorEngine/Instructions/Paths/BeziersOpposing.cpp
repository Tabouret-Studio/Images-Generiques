#include "BeziersOpposing.hpp"

Instruction * BeziersOpposing::get()
{
	return new BeziersOpposing();
}

/// OK FOR V2

std::vector<VectorImage *> BeziersOpposing::execute(std::vector<VectorImage *> &vectorImages)
{
	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				path.setStartHandle(2 * path.getStartPoint() - path.getStartHandle());
				path.setEndHandle(2 * path.getEndPoint() - path.getEndHandle());

				path.calculateBounds();
			}

			shape.calculateBounds();
		}
	}

	return vectorImages;
}
