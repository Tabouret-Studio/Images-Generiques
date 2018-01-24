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
	std::vector<std::vector<Bezier>> imagesPaths;

	for(unsigned int i=0; i<vectorImages.size(); ++i)
	{
		imagesPaths.push_back(vectorImages[i]->getBeziers());
	}

	glm::vec2 lastPos(0, 0);
	Shape shape;	

	for(std::vector<Bezier> paths : imagesPaths)
	{
		for(Bezier path : paths)
		{
			path.applyCursor();
			path.move(lastPos);
			lastPos = path.getEndPoint();

			shape << path;
		}
	}

	return {new VectorImage(vectorImages[0]->getWidth(), vectorImages[0]->getHeight(), shape)};
}
