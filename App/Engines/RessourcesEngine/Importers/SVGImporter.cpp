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
	float width, height, posX, posY, demiWidth, demiHeight;

	std::vector<Bezier> paths;
	std::vector<Shape> shapes;

	//Preload its content -> Store every path of the image as Bezier objects
	for (NSVGshape * shape = image->shapes; shape != NULL; shape = shape->next)
	{
		paths.clear();

		width = shape->bounds[2] - shape->bounds[0];
		height = shape->bounds[3] - shape->bounds[1];
		posX = shape->bounds[0];
		posY = shape->bounds[1];

		demiWidth = width / 2;
		demiHeight = height / 2;

		for (NSVGpath * path = shape->paths; path != NULL; path = path->next)
		{
			for (int i = 0; i < path->npts-1; i += 3)
			{
				p = &path->pts[i * 2];

				//TODO : Points values adjustements to be updated
				glm::vec2 startP = glm::vec2(p[0] - demiWidth, p[1] - demiHeight);
				glm::vec2 startH = glm::vec2(p[2] - demiWidth, p[3] - demiHeight);
				glm::vec2 endH = glm::vec2(p[4] - demiWidth, p[5] - demiHeight);
				glm::vec2 endP = glm::vec2(p[6] - demiWidth, p[7] - demiHeight);

				paths.push_back(Bezier(startP, startH, endH, endP));
			}
		}

		shapes.push_back(Shape(paths, shape->bounds[0],  shape->bounds[1],  shape->bounds[2],  shape->bounds[3]));
	}

	return new VectorImage(image->width, image->height, shapes);
}

