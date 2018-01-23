//
//  VectorImagesToJSONExporter.cpp
//  Xcode
//
//  Created by Valentin Dufois on 23/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "VectorImagesToJSONExporter.hpp"

#include "../Elements/VectorImage.hpp"

#include "Utils/DrawCursor.hpp"
#include "Utils/Vector/Shape.hpp"
#include "Utils/Vector/Bezier.hpp"

#include <fstream>
#include <string>
#include "Core/AppObject.hpp"

void VectorImagesToJSONExporter::exportJSON(std::vector<VectorImage *> vectorImages, const std::string &path)
{
	nlohmann::json jsonObj;

	for(VectorImage * vectorImage : vectorImages)
	{
		nlohmann::json vectorJson;

		std::vector<nlohmann::json> shapes;

		vectorJson["width"] = vectorImage->getWidth();
		vectorJson["height"] = vectorImage->getHeight();

		for(Shape &shape : vectorImage->getShapes())
		{
			nlohmann::json shapeJ;
			shapeJ["cursor"] = cursorToJson(shape.getCursor());

			for(Bezier &bezier : shape.getPaths())
			{
				nlohmann::json bezierj;
				bezierj["width"] = bezier.getDimensions().x;
				bezierj["height"] = bezier.getDimensions().y;

				bezierj["points"][0] = {{"x", bezier.getStartPoint().x}, {"y", bezier.getStartPoint().y}};
				bezierj["points"][1] = {{"x", bezier.getStartHandle().x}, {"y", bezier.getStartHandle().y}};
				bezierj["points"][2] = {{"x", bezier.getEndPoint().x}, {"y", bezier.getEndPoint().y}};
				bezierj["points"][3] = {{"x", bezier.getEndHandle().x}, {"y", bezier.getEndHandle().y}};

				bezierj["cursor"] = cursorToJson(bezier.getCursor());

				shapeJ["paths"].push_back(bezierj);
			}

			shapes.push_back(shapeJ);
		}

		vectorJson["shapes"].push_back(shapes);

		jsonObj.push_back(vectorJson);
	}

	std::ofstream f;
	std::string filePath = App->getAppPath() + path + ".json";
	f.open(filePath);

	f << jsonObj;

	f.close();
}

nlohmann::json VectorImagesToJSONExporter::cursorToJson(DrawCursor * cursor)
{
	std::vector<float> line;
	nlohmann::json j;

	for(int i = 0; i < 4; ++i)
	{
		line.clear();

		line.push_back(cursor->getMatrix()[0][0]);
		line.push_back(cursor->getMatrix()[0][1]);
		line.push_back(cursor->getMatrix()[0][2]);
		line.push_back(cursor->getMatrix()[0][3]);

		j[i] = line;
	}

	return j;
};
