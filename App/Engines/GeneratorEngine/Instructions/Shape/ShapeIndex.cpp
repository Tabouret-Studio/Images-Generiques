//
//  ShapeIndex.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ShapeIndex.hpp"
#include "Core/AppObject.hpp"
#include <math.h>

Instruction * ShapeIndex::get()
{
	return new ShapeIndex();
}

std::vector<VectorImage *> ShapeIndex::execute(std::vector<VectorImage *> &vectorImages)
{
	// Espacement entre chaque courbe
	uint boxSize = 50;
	uint demiBox = boxSize / 2;
	uint numCols = (App->getWidth() - 600) / boxSize;
	uint leftMargin = ((App->getWidth() - 600) % boxSize) / 2;

	std::vector<VectorImage *> resultat;
	glm::vec3 shapePos, shapeDim;

	// Coordonnées: 0,0 pour top-left corner
	uint col = 0, row = 0;

	// A noter: des ajustements le render de la scène sont à prévoir
	for(VectorImage* svg : vectorImages)
	{
		VectorImage * indexImage = new VectorImage();

		for(Shape shape : *svg->getShapes())
		{
			// Si on dépasse l'écran, retour à la ligne -> saut en y
			if (col >= numCols)
			{
				col = 0;
				++row;
			}

			shape.getCursor()->reset();

			//Reset path position
			shapePos = shape.getPosition();
			shapeDim = shape.getDimensions();

			//Move shape to origin
			shape.getCursor()
				->translate(-(shapePos.x + shapeDim.x / 2.0), -(shapePos.y + shapeDim.y / 2.0), 0);

			// On scale selon la dimension la plus grande
			float scale = std::min(demiBox / shapeDim.x, demiBox / shapeDim.y);

			shape.getCursor()->translate(leftMargin + col * boxSize + demiBox, row * boxSize + demiBox, 0);
			shape.getCursor()->scale(scale, scale, 1);
	
			*indexImage << shape;

			++col;
		}

		resultat.push_back(indexImage);
		
	}
	return resultat;
	
}
