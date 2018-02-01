//
//  ShapeNoise.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapeNoise.hpp"

#include "Utils/Utils.hpp"

Instruction * ShapeNoise::get()
{
	return new ShapeNoise();
}

/// OK FOR V2

std::vector<VectorImage *> ShapeNoise::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::mat4 tempCursor;
	DrawCursor modificationCursor;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			tempCursor = shape.getCursor()->getMatrix();
			modificationCursor.reset()->translate(50-Utils::rand(101), 50-Utils::rand(101), 0);

			shape.getCursor()->setMatrix(modificationCursor * tempCursor);
		}
	}

	return vectorImages;
}
