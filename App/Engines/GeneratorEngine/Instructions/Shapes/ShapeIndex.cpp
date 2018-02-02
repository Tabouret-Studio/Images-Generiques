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

/// OK FOR V2

std::vector<VectorImage *> ShapeIndex::execute(std::vector<VectorImage *> &vectorImages)
{
	// Espacement entre chaque courbe
	uint boxSize = 100;
	uint demiBox = boxSize / 2;
	uint numCols = 30;

	std::vector<VectorImage *> resultat;
	glm::vec3 shapePos, shapeDim;

	// Coordonnées: 0,0 pour top-left corner
	uint col = 0, row = 0;

	// A noter: des ajustements le render de la scène sont à prévoir
	for(VectorImage* svg : vectorImages)
	{
		for(Shape &shape : *svg->getShapes())
		{
			// Si on dépasse l'écran, retour à la ligne -> saut en y
			if (col >= numCols)
			{
				col = 0;
				++row;
			}

			shape.getCursor()->reset();

			Shape shapeTemp = shape;
			shapeTemp.applyCursor();

			//Reset path position
			shapePos = shapeTemp.getPosition();
			shapeDim = shapeTemp.getDimensions();

			//Move shape to origin
			for(Bezier &path : *shape.getPaths())
				path.getCursor()
					->translate(-(shapePos.x + shapeDim.x / 2.0), -(shapePos.y + shapeDim.y / 2.0), 0);

			// On scale selon la dimension la plus grande
			float scale = std::min(demiBox / shapeDim.x, demiBox / shapeDim.y);

			shape.getCursor()->translate(col * boxSize + demiBox, row * boxSize + demiBox, 0);
			shape.getCursor()->scale(scale, scale, 1);

			++col;
		}
	}

	return vectorImages;
}
