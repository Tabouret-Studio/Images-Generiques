//
//  ShapeNoise.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapeNoise.hpp"

#include "Utils/Utils.hpp"

Instruction * ShapeNoise::get()
{
	return new ShapeNoise();
}

/// OK FOR V2

std::vector<VectorImage *> ShapeNoise::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::mat4 tempCursor;
	DrawCursor modificationCursor;

	float intensity = m_parameters->getParam("intensity");
	float amplitude = 20.0 * intensity; float demiAmplitude = amplitude / 2.0;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			tempCursor = shape.getCursor()->getMatrix();
			modificationCursor.reset()->translate(demiAmplitude - Utils::rand(amplitude + 1), demiAmplitude -Utils::rand(amplitude + 1), 0);

			shape.getCursor()->setMatrix(modificationCursor * tempCursor);
		}
	}

	return vectorImages;
}
