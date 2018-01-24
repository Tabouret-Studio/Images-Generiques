//
//  SVGImporter.cpp
//  Xcode
//
//  Created by Valentin Dufois on 14/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#define NANOSVG_IMPLEMENTATION
#include "libraries.hpp"

#include "SVGImporter.hpp"

#include "../Elements/Vector/VectorImage.hpp"
#include "Elements/Vector/Bezier.hpp"
#include "Elements/Vector/Shape.hpp"

#include "Core/AppObject.hpp"

#include <vector>

Asset * SVGImporter::getAsset(const std::string &path)
{
	NSVGimage * image = nsvgParseFromFile(path.c_str(), "px", 96);

	float * p;
	float pathMinX, pathMinY, pathMaxX, pathMaxY;

	glm::vec3 shapePos, shapeDim, shapeDemiDim;
	glm::vec2 pathPos, pathDim;

	std::vector<Bezier> paths;
	std::vector<Shape> shapes;
	std::vector<glm::vec3> points;
	Bezier curve;

	//Preload its content -> Store every path of the image as Bezier objects
	for (NSVGshape * shape = image->shapes; shape != NULL; shape = shape->next)
	{
		paths.clear();

		//Get shape coordinates
		shapePos = glm::vec3(shape->bounds[0], shape->bounds[1], 0);
		shapeDim = glm::vec3(shape->bounds[2] - shape->bounds[0], shape->bounds[3] - shape->bounds[1], 0);

		//Parse the shape's paths
		for (NSVGpath * path = shape->paths; path != NULL; path = path->next)
		{
			for (int i = 0; i < path->npts-1; i += 3)
			{
				p = &path->pts[i * 2];

				//Path coordinates
				glm::vec3 startP = glm::vec3(p[0], p[1], 0);
				glm::vec3 startH = glm::vec3(p[2], p[3], 0);
				glm::vec3 endH = glm::vec3(p[4], p[5], 0);
				glm::vec3 endP = glm::vec3(p[6], p[7], 0);

				//Create curve
				curve = Bezier(startP, startH, endH, endP);

				//Calculate bezier coordinates
				points = curve.getPoints();

				pathMinX = points[0].x; pathMaxX = points[0].x;
				pathMinY = points[0].y; pathMaxY = points[0].y;

				for(std::vector<glm::vec3>::const_iterator it = points.begin()+1; it != points.end(); ++it)
				{
					if((*it).x < pathMinX) pathMinX = (*it).x;
					if((*it).x > pathMaxX) pathMaxX = (*it).x;
					if((*it).y < pathMinY) pathMinY = (*it).y;
					if((*it).y > pathMaxY) pathMaxY = (*it).y;
				}

				pathPos = glm::vec2(pathMinX, pathMinY);
				pathDim = glm::vec2(pathMaxX - pathMinX, pathMaxY - pathMinY);

				//Store curve dimensions
				curve.setDimensions(pathDim.x, pathDim.y, 0);

				//Move bezier to origin
				curve.getCursor()
					->translate(-(pathPos.x + pathDim.x / 2.0), -(pathPos.y + pathDim.y / 2.0), 0);
				curve.applyCursor();

				curve.getCursor()
					->translate(pathPos.x + pathDim.x / 2.0, pathPos.y + pathDim.y / 2.0, 0);

				paths.push_back(curve);
			}
		}

		Shape renderedShape(paths);
		renderedShape.getCursor()->translate(-image->width / 2.0, -image->height / 2, 0);

		shapes.push_back(renderedShape);
	}

	return new VectorImage(image->width, image->height, shapes);
}

