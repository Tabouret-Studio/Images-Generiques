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

	glm::vec3 shapePos, shapeDim, shapeDemiDim;
	glm::vec3 bezierPos, bezierDim;

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

				bezierPos = curve.getPosition();
				bezierDim = curve.getDimensions();

				//Move bezier to origin
				curve.getCursor()
					->translate(-(bezierPos.x + bezierDim.x / 2.0), -(bezierPos.y + bezierDim.y / 2.0), 0);
				curve.applyCursor();

				curve.getCursor()
					->translate(bezierPos.x + bezierDim.x / 2.0, bezierPos.y + bezierDim.y / 2.0, 0);

				paths.push_back(curve);
			}
		}

		Shape renderedShape(paths);
		renderedShape.getCursor()->translate(-image->width / 2.0, -image->height / 2, 0);

		shapes.push_back(renderedShape);
	}

	return new VectorImage(image->width, image->height, shapes);
}

