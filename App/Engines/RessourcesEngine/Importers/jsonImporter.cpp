#include "libraries.hpp"

#include "jsonImporter.hpp"

#include "../Elements/jsonObject.hpp"
#include "Core/AppObject.hpp"

#include <vector>
#include <fstream>

Asset * jsonImporter::getAsset(const std::string &path)
{
	// read a JSON file
	std::ifstream jsonFile("file.json");
	nlohmann::json * j = new nlohmann::json();
	jsonFile >> *j;

	return new jsonObject(j);
}