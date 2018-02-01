#include "ShapesGeometryRandomizer.hpp"
#include "Utils/Utils.hpp"

Instruction * ShapesGeometryRandomizer::get()
{
	return new ShapesGeometryRandomizer();
}

/// OK FOR V2

std::vector<VectorImage *> ShapesGeometryRandomizer::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::vec3 shapePos, shapeDim;

	glm::mat4 tempCursor;
	DrawCursor modificationCursor;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			tempCursor = shape.getCursor()->getMatrix();

			shape.getCursor()->reset();

			modificationCursor.rotate(float(1 - Utils::rand(3)) / 2.0, 0, 0, 1);

			shape.getCursor()->setMatrix(modificationCursor.getMatrix() * tempCursor);
		}
	}

	return vectorImages;
}
