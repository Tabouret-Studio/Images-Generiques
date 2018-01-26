//  Created by Marie-Lou Barbier on 25/01/2018.

#include "JSONExporter.hpp"
#include "Core/AppObject.hpp"

#include <fstream>

void JSONExporter::exportJSON(const nlohmann::json &j, const std::string &fileName) {
    std::ofstream indexExport(App->getAppPath()+"/indexLibrary"+fileName+".json");
    indexExport << j;
    indexExport.close();
}