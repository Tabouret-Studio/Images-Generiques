//
//  ShapesScatterCircle.cpp
//  Xcode
//
//  Created by Valentin Dufois on 01/02/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapesScatterCircle.hpp"
#include "Utils/Utils.hpp"

Instruction * ShapesScatterCircle::get()
{
	return new ShapesScatterCircle();
}

/// OK FOR V2

std::vector<VectorImage *> ShapesScatterCircle::execute(std::vector<VectorImage *> &vectorImages)
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

			Shape shapeTemp = shape;
			shapeTemp.applyCursor();

			//Reset path position
			shapePos = shapeTemp.getPosition();
			shapeDim = shapeTemp.getDimensions();

			std::cout << glm::to_string(shapePos) << glm::to_string(shapeDim) << std::endl;

			//Move shape to origin
			for(Bezier &path : *shape.getPaths())
				path.getCursor()
				->translate(-(shapePos.x + shapeDim.x / 2.0), -(shapePos.y + shapeDim.y / 2.0), 0);

			modificationCursor.rotate(5 - Utils::rand(11), 0, 0, 1);

			shape.getCursor()->setMatrix(modificationCursor * tempCursor);
		}
	}

	return vectorImages;
}
