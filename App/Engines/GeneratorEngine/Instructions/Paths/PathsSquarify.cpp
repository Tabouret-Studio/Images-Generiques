//
//  PathsSquarify.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PathsSquarify.hpp"

Instruction * PathsSquarify::get()
{
	return new PathsSquarify();
}

/// OK FOR V2

std::vector<VectorImage *> PathsSquarify::execute(std::vector<VectorImage *> &vectorImages)
{
	glm::mat4 tempCursor;

	glm::vec3 vec_starthandle, startpoint, endpoint;
	Bezier vertical, horizontal;

	std::vector<Bezier> newPaths;

	for(VectorImage * vImage : vectorImages)
	{
		for(Shape &shape : *vImage->getShapes())
		{
			for(Bezier &path : *shape.getPaths())
			{
				Bezier tempPath = path;
				//tempPath.applyCursor();

				//Check for already lined up paths
				if((tempPath.getStartPoint().x == tempPath.getStartHandle().x &&
					tempPath.getStartPoint().x == tempPath.getEndHandle().x &&
					tempPath.getStartPoint().x == tempPath.getEndPoint().x
					) || (
					tempPath.getStartPoint().y == tempPath.getStartHandle().y &&
				    tempPath.getStartPoint().y == tempPath.getEndHandle().y &&
				    tempPath.getStartPoint().y == tempPath.getEndPoint().y))
				{
					continue;
				}

				//path = tempPath;

				tempCursor = path.getCursor()->getMatrix();
				path.getCursor()->reset();
				
				startpoint = path.getStartPoint();
				endpoint = path.getEndPoint();
				vec_starthandle = path.getStartHandle() - path.getStartPoint();

				if(vec_starthandle.x > vec_starthandle.y)
				{
					vertical = Bezier(startpoint, glm::vec3(endpoint.x, startpoint.y, 0),
									  startpoint, glm::vec3(endpoint.x, startpoint.y, 0));

					horizontal = Bezier(glm::vec3(endpoint.x, startpoint.y, 0), endpoint,
									    glm::vec3(endpoint.x, startpoint.y, 0), endpoint);
				}
				else
				{
					vertical = Bezier(startpoint, glm::vec3(startpoint.x, endpoint.y, 0),
									  startpoint, glm::vec3(startpoint.x, endpoint.y, 0));

					horizontal = Bezier(glm::vec3(startpoint.x, endpoint.y, 0), endpoint,
										glm::vec3(startpoint.x, endpoint.y, 0), endpoint);
				}

				vertical.getCursor()->setMatrix(tempCursor);
				path = vertical;

				horizontal.getCursor()->setMatrix(tempCursor);
				newPaths.push_back(horizontal);
			}

			shape.getPaths()->insert(shape.getPaths()->end(), newPaths.begin(), newPaths.end());
			newPaths.clear();
		}
	}

	return vectorImages;
}
