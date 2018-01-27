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

std::vector<VectorImage *> PathsNoise::execute(const std::vector<VectorImage *> &vectorImages)
{
	
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();

	glm::vec2 lastPos(0, 0);
	Shape shape;

	for(Bezier path : paths)
	{
		path.applyCursor();
		path.move(path.getStartPoint()+glm::vec3(rand()%100,rand()%100, 0));

		shape << path;
	}

	return {new VectorImage(shape)};
}
