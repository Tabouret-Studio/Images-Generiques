//
//  PathsNoise.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsNoise.hpp"
#include "Utils/Utils.hpp"

Instruction * PathsNoise::get()
{
	return new PathsNoise();
}

/// OK FOR V2

std::vector<VectorImage *> PathsNoise::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::mat4 tempCursor;
	DrawCursor modificationCursor;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				tempCursor = path.getCursor()->getMatrix();
				modificationCursor.reset()->translate(5.0 - Utils::rand(11), 5.0 - Utils::rand(11), 0);

				path.getCursor()->setMatrix(modificationCursor * tempCursor);
			}
		}
	}

	return vectorImages;
}
