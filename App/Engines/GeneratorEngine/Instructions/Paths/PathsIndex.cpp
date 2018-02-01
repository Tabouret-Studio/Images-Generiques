//
//  PathsIndex.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsIndex.hpp"
#include "Core/AppObject.hpp"
#include <math.h>

Instruction * PathsIndex::get()
{
	return new PathsIndex();
}

/// OK FOR V2

std::vector<VectorImage *> PathsIndex::execute(std::vector<VectorImage *> &vectorImages)
{
	// Espacement entre chaque courbe
	uint boxSize = 100;
	uint demiBox = boxSize /2;
	uint numCols = 40;

	VectorImage * output = new VectorImage();
	glm::vec3 bezierPos, bezierDim;

	// Coordonnées: 0,0 pour top-left corner
	uint col = 0, row = 0;

	// A noter: des ajustements le render de la scène sont à prévoir
	for(VectorImage * svg : vectorImages)
	{
		Shape vectorShape;

		for(Shape &shape : *svg->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				// Si on dépasse l'écran, retour à la ligne -> saut en y
				if (col >= numCols)
				{
					col = 0;
					++row;
				}

				path.getCursor()->reset();

				//Reset path position
				bezierPos = path.getPosition();
				bezierDim = path.getDimensions();

				//Move bezier to origin
				path.getCursor()
					->translate(-(bezierPos.x + bezierDim.x / 2.0), -(bezierPos.y + bezierDim.y / 2.0), 0);

				// On scale selon la dimension la plus grande
				float scale = std::min(demiBox / bezierDim.x, demiBox / bezierDim.y);

				//Place bezier on grid
				path.getCursor()->translate(col * boxSize + demiBox, row * boxSize + demiBox, 0);
				path.getCursor()->scale(scale, scale, 1);

				vectorShape << path;


				++col;
			}
		}

		*output << vectorShape;

		//shape.getCursor()->translate(-(App->getWidth() - 600) / 2, 0, 0);
	}

	return {output};
}
