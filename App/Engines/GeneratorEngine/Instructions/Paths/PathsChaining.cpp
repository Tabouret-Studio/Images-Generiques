//
//  PathsChaining.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsChaining.hpp"

Instruction * PathsChaining::get()
{
	return new PathsChaining();
}

/// OK FOR V2

std::vector<VectorImage *> PathsChaining::execute(std::vector<VectorImage *> &vectorImages)
{
	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			glm::vec3 lastPos(0, 0, 0);

			for(Bezier &path : *shape.getPaths())
			{
				path.applyCursor();
				path.move(lastPos);
				lastPos = path.getEndPoint();
			}
		}
	}

	return vectorImages;
}
