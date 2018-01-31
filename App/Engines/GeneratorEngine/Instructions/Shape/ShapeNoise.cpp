//
//  ShapeNoise.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapeNoise.hpp"

Instruction * ShapeNoise::get()
{
	return new ShapeNoise();
}

std::vector<VectorImage *> ShapeNoise::execute(const std::vector<VectorImage *> &vectorImages)
{
	vectorImages[0]->applyCursor();

	std::vector<Shape> shapes = vectorImages[0]->getShapes();

	glm::vec2 lastPos(0, 0);
	VectorImage* svg=new VectorImage();

	glm::vec3 refpoint;

	for(Shape shape : shapes)
	{

		shape.applyCursor();
		refpoint=shape.getPaths()[0].getStartPoint();
		shape.move(refpoint+glm::vec3(rand()%100,rand()%100, 0));

		*svg << shape;
	}

	return {svg};
}
