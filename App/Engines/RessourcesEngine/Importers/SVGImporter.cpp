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

	std::vector<Bezier> paths;
	std::vector<Shape> shapes;

	//Preload its content -> Store every path of the image as Bezier objects
	for (NSVGshape * shape = image->shapes; shape != NULL; shape = shape->next)
	{
		paths.clear();

		for (NSVGpath * path = shape->paths; path != NULL; path = path->next)
		{

			for (int i = 0; i < path->npts-1; i += 3)
			{
				p = &path->pts[i * 2];

				//TODO : Points values adjustements to be updated
				glm::vec2 startP = glm::vec2(p[0], p[1]);
				glm::vec2 startH = glm::vec2(p[2], p[3]);
				glm::vec2 endH = glm::vec2(p[4], p[5]);
				glm::vec2 endP = glm::vec2(p[6], p[7]);

				paths.push_back(Bezier(startP, startH, endH, endP));
			}
		}

		shapes.push_back(Shape(paths, shape->bounds[0],  shape->bounds[1],  shape->bounds[2],  shape->bounds[3]));
	}

	return new VectorImage(image->width, image->height, shapes);
}

