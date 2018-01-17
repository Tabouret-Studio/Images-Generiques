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

#include "../Elements/VectorImage.hpp"
#include "Utils/Vector/Bezier.hpp"
#include "Utils/Vector/Shape.hpp"

#include <vector>

Asset * SVGImporter::getAsset(const std::string &path)
{
	NSVGimage * image = nsvgParseFromFile(path.c_str(), "px", 96);

	float * p;
	float ShapeWidth, ShapeHeight, ShapePosX, ShapePosY, ShapeDemiWidth, ShapeDemiHeight;
	float pathMinX, pathMinY, pathMaxX, pathMaxY, pathWidth, pathHeight;

	std::vector<Bezier> paths;
	std::vector<Shape> shapes;
	std::vector<glm::vec2> points;
	Bezier curve;

	//Preload its content -> Store every path of the image as Bezier objects
	for (NSVGshape * shape = image->shapes; shape != NULL; shape = shape->next)
	{
		paths.clear();

		ShapeWidth = shape->bounds[2] - shape->bounds[0];
		ShapeHeight = shape->bounds[3] - shape->bounds[1];
		ShapePosX = shape->bounds[0];
		ShapePosY = shape->bounds[1];

		ShapeDemiWidth = ShapeWidth / 2.0;
		ShapeDemiHeight = ShapeHeight / 2.0;

		for (NSVGpath * path = shape->paths; path != NULL; path = path->next)
		{
			for (int i = 0; i < path->npts-1; i += 3)
			{
				p = &path->pts[i * 2];

				glm::vec2 startP = glm::vec2(p[0] - ShapeDemiWidth, p[1] - ShapeDemiHeight);
				glm::vec2 startH = glm::vec2(p[2] - ShapeDemiWidth, p[3] - ShapeDemiHeight);
				glm::vec2 endH = glm::vec2(p[4] - ShapeDemiWidth, p[5] - ShapeDemiHeight);
				glm::vec2 endP = glm::vec2(p[6] - ShapeDemiWidth, p[7] - ShapeDemiHeight);

				curve = Bezier(startP, startH, endH, endP);

				//Calculate bounds
				points = curve.getPoints();

				pathMinX = points[0].x; pathMaxX = points[0].x;
				pathMinY = points[0].y; pathMaxY = points[0].y;

				for(std::vector<glm::vec2>::const_iterator it = points.begin()+1; it != points.end(); ++it)
				{
					if((*it).x < pathMinX) pathMinX = (*it).x;
					if((*it).x > pathMaxX) pathMaxX = (*it).x;
					if((*it).y < pathMinY) pathMinY = (*it).y;
					if((*it).y > pathMaxY) pathMaxY = (*it).y;
				}

				pathWidth = pathMaxX - pathMinX;
				pathHeight = pathMaxY - pathMinY;

				curve.getCursor()
					->translate(-(pathMinX + pathWidth / 2.0), -(pathMinY + pathHeight / 2.0), 0);
				curve.applyCursor();

				curve.getCursor()
					->translate(pathMinX + pathWidth / 2.0, pathMinY + pathHeight / 2.0, 0);

				curve.setDimensions(pathWidth, pathHeight);

				paths.push_back(curve);
			}
		}

		shapes.push_back(Shape(paths, ShapePosX, ShapePosY, ShapeWidth, ShapeHeight));
	}

	return new VectorImage(image->width, image->height, shapes);
}

