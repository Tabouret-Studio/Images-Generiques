//
//  PathsNoise.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsNoise.hpp"

Instruction * PathsNoise::get()
{
	return new PathsNoise();
}

/// OK FOR V2

std::vector<VectorImage *> PathsNoise::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::mat4 tempCursor;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				tempCursor = path.getCursor()->getMatrix();
				path.getCursor()->reset()->translate(rand()%11 - 5, rand()%11 - 5, 0);
				path.applyCursor();
				path.getCursor()->setMatrix(tempCursor);
			}
		}
	}

	return vectorImages;
}
