//
//  PathsOrderRandomizer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsOrderRandomizer.hpp"

#include "Core/AppObject.hpp"

Instruction * PathsOrderRandomizer::get()
{
	return new PathsOrderRandomizer();
}

VectorImage * PathsOrderRandomizer::execute(VectorImage * vectorImage)
{
	std::vector<Bezier> paths = vectorImage->getBeziers();
	std::random_shuffle(paths.begin(), paths.end(), App->rand);

	return new VectorImage(vectorImage->getWidth(), vectorImage->getHeight(), Shape(paths));
}
