//  Created by Marie-Lou Barbier on 25/01/2018.

#include "JSONExporter.hpp"
#include "Core/AppObject.hpp"

#include <fstream>

void JSONExporter::exportJSON(const nlohmann::json &j, const std::string &fileName)
{
	std::string filepath = App->getAppPath() + fileName + ".json";
    std::ofstream indexExport(filepath);

	if(!indexExport)
	{
		std::cout << "Could not export library index." << std::endl;
	}

    indexExport << j;
    indexExport.close();
}
