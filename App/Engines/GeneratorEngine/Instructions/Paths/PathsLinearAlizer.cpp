#include "PathsLinearAlizer.hpp"

Instruction * PathsLinearAlizer::get()
{
	return new PathsLinearAlizer();
}

/// OK FOR V2

std::vector<VectorImage *> PathsLinearAlizer::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::mat4 tempCursor;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				tempCursor = path.getCursor()->getMatrix();

				path = Bezier(path.getStartPoint(),path.getEndPoint(),path.getStartPoint(),path.getEndPoint());
				path.getCursor()->setMatrix(tempCursor);
			}
		}
	}

	return vectorImages;
}
