//
//  VectorImagesToJSONExporter.cpp
//  Xcode
//
//  Created by Valentin Dufois on 23/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "VectorImagesToJSONExporter.hpp"

#include "../Elements/Vector/VectorImage.hpp"

#include "Utils/DrawCursor.hpp"
#include "Elements/Vector/Shape.hpp"
#include "Elements/Vector/Bezier.hpp"

#include <fstream>
#include <string>
#include "Core/AppObject.hpp"

void VectorImagesToJSONExporter::exportJSON(std::vector<VectorImage *> vectorImages, const std::string &path)
{
	nlohmann::json jsonObj;

	for(VectorImage * vectorImage : vectorImages)
	{
		nlohmann::json vectorJson;

		vectorJson["width"] = vectorImage->getDimensions().x;
		vectorJson["height"] = vectorImage->getDimensions().y;

		for(Shape &shape : *vectorImage->getShapes())
		{
			nlohmann::json shapeJ;
			shapeJ["cursor"] = cursorToJson(shape.getCursor());

			for(Bezier &bezier : *shape.getPaths())
			{
				nlohmann::json bezierj;
				bezierj["width"] = bezier.getDimensions().x;
				bezierj["height"] = bezier.getDimensions().y;
				bezierj["depth"] = bezier.getDimensions().z;

				bezierj["points"] = {
					{{"x", bezier.getStartPoint().x}, {"y", bezier.getStartPoint().y}, {"z", bezier.getStartPoint().z}},
					{{"x", bezier.getStartHandle().x}, {"y", bezier.getStartHandle().y}, {"z", bezier.getStartHandle().z}},
					{{"x", bezier.getEndHandle().x}, {"y", bezier.getEndHandle().y}, {"z", bezier.getStartHandle().z}},
					{{"x", bezier.getEndPoint().x}, {"y", bezier.getEndPoint().y}, {"z", bezier.getEndPoint().z}}};

				bezierj["cursor"] = cursorToJson(bezier.getCursor());

				shapeJ["paths"].push_back(bezierj);
			}

			vectorJson["shapes"].push_back(shapeJ);
		}

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

		line.push_back(cursor->getMatrix()[i][0]);
		line.push_back(cursor->getMatrix()[i][1]);
		line.push_back(cursor->getMatrix()[i][2]);
		line.push_back(cursor->getMatrix()[i][3]);

		j[i] = line;
	}

	return j;
}
