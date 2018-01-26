//
//  PathsOrientRandomizer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsOrientRandomizer.hpp"
#include "Utils/Utils.hpp"

Instruction * PathsOrientRandomizer::get()
{
	return new PathsOrientRandomizer();
}

std::vector<VectorImage *> PathsOrientRandomizer::execute(std::vector<VectorImage *> vectorImages)
{
	
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();

	Shape shape;

	for(Bezier path : paths)
	{
		
		path.getCursor()->rotate(Utils::rand(360),0,0,1);
		path.applyCursor();

		shape << path;
	}

	return {new VectorImage(vectorImages[0]->getWidth(), vectorImages[0]->getHeight(), shape)};
}
