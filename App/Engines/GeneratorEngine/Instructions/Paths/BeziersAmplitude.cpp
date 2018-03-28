#include "BeziersAmplitude.hpp"

Instruction * BeziersAmplitude::get()
{
	return new BeziersAmplitude();
}

/// OK FOR V2

std::vector<VectorImage *> BeziersAmplitude::execute(std::vector<VectorImage *> &vectorImages)
{
	float intensity = m_parameters->getParam("intensity");
	float amplitude = 1.05 * intensity;

	//if(amplitude == 0)
	//	return;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				path.setStartHandle(path.getStartHandle() * amplitude);
				path.setEndHandle(path.getEndHandle() * amplitude);

				path.calculateBounds();
			}

			shape.calculateBounds();
		}
	}

	return vectorImages;
}
