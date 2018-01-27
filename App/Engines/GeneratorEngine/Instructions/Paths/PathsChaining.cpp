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

std::vector<VectorImage *> PathsChaining::execute(std::vector<VectorImage *> vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();

	glm::vec3 lastPos(0, 0, 0);
	Shape shape;

	for(Bezier path : paths)
	{
		path.applyCursor();
		path.move(lastPos);
		lastPos = path.getEndPoint();

		shape << path;
	}

	return {new VectorImage(shape)};
}
