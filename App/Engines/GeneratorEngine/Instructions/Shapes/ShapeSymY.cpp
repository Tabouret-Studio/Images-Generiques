//
//  ShapeSymY.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapeSymY.hpp"

Instruction * ShapeSymY::get()
{
	return new ShapeSymY();
}

/// OK FOR V2

std::vector<VectorImage *> ShapeSymY::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::mat4 tempCursor;
	DrawCursor modificationCursor;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			tempCursor = shape.getCursor()->getMatrix();
			modificationCursor.reset()->scale(1, -1, 1);

			shape.getCursor()->setMatrix(modificationCursor * tempCursor);
		}
	}

	return vectorImages;
}
