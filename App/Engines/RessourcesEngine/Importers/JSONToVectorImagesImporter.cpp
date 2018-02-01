//
//  JSONToVectorImagesImporter.cpp
//  Xcode
//
//  Created by Valentin Dufois on 23/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "JSONToVectorImagesImporter.hpp"

#include "Core/AppObject.hpp"
#include "../Elements/Vector/VectorImage.hpp"
#include "Elements/Vector/Shape.hpp"
#include "Elements/Vector/Bezier.hpp"

#include <fstream>

std::vector<VectorImage *> JSONToVectorImagesImporter::import(const std::string &path)
{
	//Vector images containers
	std::vector<VectorImage *> vectorImages;

	//Open file
	std::string filePath = App->getAppPath() + path + ".json";
	std::ifstream file(filePath);

	if(!file)
		return vectorImages;

	std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	nlohmann::json jsonOutput = nlohmann::json::parse(content);

	//For each VectorImage in the file
	for(const nlohmann::json &jsonVector : jsonOutput)
	{
		VectorImage * vectorImage = new VectorImage();

		//For each Shape in the VectorImage
		for(const nlohmann::json &shapeJson : jsonVector["shapes"])
		{
			Shape shape;
			shape.getCursor()->setMatrix(convertMatrix(shapeJson["cursor"]));

			for(const nlohmann::json &jBez : shapeJson["paths"].get<nlohmann::json>())
			{
				Bezier bezier(jBez["points"][0]["x"], jBez["points"][0]["y"],
							  jBez["points"][1]["x"], jBez["points"][1]["y"],
							  jBez["points"][2]["x"], jBez["points"][2]["y"],
							  jBez["points"][3]["x"], jBez["points"][3]["y"]);

				bezier.getCursor()->setMatrix(convertMatrix(jBez["cursor"].get<nlohmann::json>()));

				shape << bezier;
			}

			*vectorImage << shape;
		}

		vectorImages.push_back(vectorImage);
	}

	return vectorImages;
}

glm::mat4 JSONToVectorImagesImporter::convertMatrix(const nlohmann::json &jsonMat)
{
	glm::vec4
		line1(jsonMat[0][0].get<float>(), jsonMat[0][1].get<float>(), jsonMat[0][2].get<float>(), jsonMat[0][3].get<float>()),
		line2(jsonMat[1][0].get<float>(), jsonMat[1][1].get<float>(), jsonMat[1][2].get<float>(), jsonMat[1][3].get<float>()),
		line3(jsonMat[2][0].get<float>(), jsonMat[2][1].get<float>(), jsonMat[2][2].get<float>(), jsonMat[2][3].get<float>()),
		line4(jsonMat[3][0].get<float>(), jsonMat[3][1].get<float>(), jsonMat[3][2].get<float>(), jsonMat[3][3].get<float>());

	return glm::mat4(line1, line2, line3, line4);
}
