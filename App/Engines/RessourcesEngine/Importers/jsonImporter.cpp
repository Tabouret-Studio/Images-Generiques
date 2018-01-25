#include "libraries.hpp"

#include "jsonImporter.hpp"

#include "../Elements/jsonObject.hpp"
#include "Core/AppObject.hpp"

#include <vector>
#include <fstream>

Asset * jsonImporter::getAsset(const std::string &path)
{
	//Check if file exists
	if(!App->ressourcesEngine->fileExist(path)) {
		throw std::runtime_error("The file "+path+".json could not be loaded");
	}

	// read a JSON file
	std::ifstream jsonFile;
	jsonFile.open(path);
	
	std::string content((std::istreambuf_iterator<char>(jsonFile)), (std::istreambuf_iterator<char>()));
	nlohmann::json * j = new nlohmann::json();
	*j = nlohmann::json::parse(content);

	return new jsonObject(j);
}