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
	glm::vec3 bezierPos, bezierDim, lastPos;

	for(VectorImage * vImage : vectorImages)
	{
		vImage->getCursor()->reset();
		lastPos = glm::vec3(0, 0, 0);

		for(Shape &shape : *vImage->getShapes())
		{
			shape.getCursor()->reset();

			for(Bezier &path : *shape.getPaths())
			{
				bezierPos = path.getPosition();
				bezierDim = path.getDimensions();

				//Move bezier to origin
				path.getCursor()
					->reset()
					->translate(-(bezierPos.x + bezierDim.x / 2.0), -(bezierPos.y + bezierDim.y / 2.0), 0);

				//Move bezier start point to origin
				path.getCursor()
					->translate(-path.getStartPoint());

				//Move besier to lastPos
				path.getCursor()
					->translate(lastPos);

				Bezier pathTemp = path;
				pathTemp.applyCursor();

				std::cout << glm::to_string(lastPos) << std::endl;
				lastPos = pathTemp.getEndPoint();
			}
		}
	}

	return vectorImages;
}
