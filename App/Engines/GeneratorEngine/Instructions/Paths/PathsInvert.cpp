//
//  PathsInvert.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsInvert.hpp"

Instruction * PathsInvert::get()
{
	return new PathsInvert();
}

/// OK FOR V2

std::vector<VectorImage *> PathsInvert::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::vec3
		symline, // axe de symétrie
		starthandle, endhandle, // vecteur poigné
		starthandleprojected, endhandleprojected, // projeté des vecteurs poigné sur symline
		starthandlegap, endhandlegap, // vecteur décrivant la projection opérée
		starthandlesym, endhandlesym; // coordonné de la symétrie

	glm::mat4 tempCursor;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				tempCursor = path.getCursor()->getMatrix();
				path.getCursor()->reset();

				starthandle = path.getStartHandle() - path.getStartPoint();
				endhandle = path.getEndHandle()  -path.getEndPoint();
				symline = glm::normalize(path.getEndPoint() - path.getStartPoint());

				starthandleprojected = glm::dot(symline, starthandle) * symline;
				starthandlegap = (path.getStartPoint() + starthandleprojected) - path.getStartHandle();
				starthandlesym=path.getStartHandle()+2*starthandlegap;

				endhandleprojected = glm::dot(symline, endhandle) * symline;
				endhandlegap = (path.getEndPoint() + endhandleprojected) - path.getEndHandle();
				endhandlesym = path.getEndHandle() + 2 * endhandlegap;

				path = Bezier(path.getStartPoint(), starthandlesym, endhandlesym, path.getEndPoint());

				path.getCursor()->setMatrix(tempCursor);
			}
		}
	}

	return vectorImages;
}
