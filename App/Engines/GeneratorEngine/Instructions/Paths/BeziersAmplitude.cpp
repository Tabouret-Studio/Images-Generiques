#include "BeziersAmplitude.hpp"

Instruction * BeziersAmplitude::get()
{
	return new BeziersAmplitude();
}

/// OK FOR V2

std::vector<VectorImage *> BeziersAmplitude::execute(std::vector<VectorImage *> &vectorImages)
{

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				path.setStartHandle(path.getStartHandle() * 2);
				path.setEndHandle(path.getEndHandle() * 2);
			}
		}
	}

	return vectorImages;
}
