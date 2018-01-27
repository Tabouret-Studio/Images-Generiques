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

std::vector<VectorImage *> PathsSquarify::execute(const std::vector<VectorImage *> &vectorImages)
{
	
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	Shape shape;

	glm::vec3 vec_starthandle, startpoint, endpoint;
	Bezier vertical, horizontal;

	for(Bezier path : paths)
	{
		path.applyCursor();
		startpoint = path.getStartPoint();
		endpoint = path.getEndPoint();
		vec_starthandle = path.getStartHandle() - path.getStartPoint();

		if(vec_starthandle.x > vec_starthandle.y)
		{
			horizontal = Bezier(startpoint, glm::vec3(endpoint.x,startpoint.y, 0),
								startpoint, glm::vec3(endpoint.x,startpoint.y, 0));
			shape << horizontal;

			vertical = Bezier(glm::vec3(endpoint.x, startpoint.y, 0), endpoint,
							  glm::vec3(endpoint.x, startpoint.y, 0), endpoint);
			shape << vertical;
		}
		else
		{
			vertical = Bezier(startpoint, glm::vec3(startpoint.x, endpoint.y, 0),
							  startpoint, glm::vec3(startpoint.x, endpoint.y, 0));
			shape << vertical;

			horizontal= Bezier(glm::vec3(startpoint.x, endpoint.y, 0), endpoint,
							   glm::vec3(startpoint.x, endpoint.y, 0), endpoint
			);
			shape << horizontal;
		}
	}

	return {new VectorImage(shape)};
}
