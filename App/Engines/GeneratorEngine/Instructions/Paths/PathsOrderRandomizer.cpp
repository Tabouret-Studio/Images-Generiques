//
//  PathsOrderRandomizer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsOrderRandomizer.hpp"

#include "Utils/Utils.hpp"

Instruction * PathsOrderRandomizer::get()
{
	return new PathsOrderRandomizer();
}

std::vector<VectorImage *> PathsOrderRandomizer::execute(const std::vector<VectorImage *> &vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	std::random_shuffle(paths.begin(), paths.end(), Utils::rand);

	return {new VectorImage(Shape(paths))};
}
