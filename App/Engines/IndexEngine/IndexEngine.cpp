//  Created by Marie-Lou Barbier on 19/01/2018.


#include "IndexEngine.hpp"

#include "Core/AppObject.hpp"
#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"
#include "Engines/RessourcesEngine/Importers/JSONImporter.hpp"
#include "Engines/RessourcesEngine/Exporters/JSONExporter.hpp"

#include <fstream>

bool IndexEngine::m_instanciated = false;

/**
 * Instanciate the engine as a Singleton
 */
void IndexEngine::instanciate()
{
	if(m_instanciated)
		return;

	App->indexEngine = new IndexEngine();

	m_instanciated = true;
}

/**
 * Private constructor
 */
IndexEngine::IndexEngine() {
	loadLibrary();
}


void IndexEngine::loadLibrary() {
	JSONImporter jsonImport;
	jsonObject * jsonFile = *jsonImport.getAsset(App->getAppPath()+"/indexLibrary/indexLibrary.json");
	
	nlohmann::json * j = jsonFile->get(); 
	
	nlohmann::json imagesList = (*j)["images"];

	for(const nlohmann::json &jsonImage : imagesList)
	{
		srcId imgId = App->genUUID();
		m_ImagesIdsPaths.insert(std::pair<srcId, std::string>(imgId, jsonImage["path"].get<std::string>()));
		m_ImagesIdsTags.insert(std::pair<srcId, std::vector<std::string>>(imgId, jsonImage["tags"].get<std::vector<std::string>>()));

	}
}

bool IndexEngine::imageIdIsValid(const srcId &imgId) const {
	if(m_ImagesIdsPaths.find(imgId) == m_ImagesIdsPaths.end())
		return false;

	return true;
}


std::vector<srcId> * IndexEngine::getImagesIds() const
{
	std::vector<srcId> * imagesIds = new std::vector<srcId>();

	for(std::map<srcId, std::string>::const_iterator it = m_ImagesIdsPaths.begin(); it != m_ImagesIdsPaths.end(); ++it)
	{
		imagesIds->push_back(it->first);
	}

	return imagesIds;
}

VectorImage * IndexEngine::getVectorImage(const srcId &imgId) const
{
	rId vecId = App->ressourcesEngine->loadAsset(m_ImagesIdsPaths.at(imgId), VECTOR);
	return *App->ressourcesEngine->getAsset(vecId);
}

std::vector<std::string> IndexEngine::getImageTags(const srcId &imgId) const
{
	if(!imageIdIsValid(imgId)) {
		throw std::runtime_error("Given ID is not a valid imgId.");
	}

	return m_ImagesIdsTags.at(imgId);
}

void IndexEngine::insertVectorIMage(const VectorImage * image, const std::vector<std::string> &tags)
{
	SVGExporter exporter;
	std::string title = std::to_string(SDL_GetTicks());
	exporter.exportSVG(image, title);

	srcId imgId = App->genUUID();

	m_ImagesIdsPaths.insert(std::pair<srcId, std::string>(imgId, "indexLibrary/"+title+".svg"));
	m_ImagesIdsTags.insert(std::pair<srcId, std::vector<std::string>>(imgId, tags));
}

void IndexEngine::exportIndexToJSON() const
{
	nlohmann::json imagesToJSON;

	for(std::map<srcId, std::string>::const_iterator it = m_ImagesIdsPaths.begin(); it != m_ImagesIdsPaths.end(); ++it)
	{
		nlohmann::json imageJSON;
		
		imageJSON["path"] = (*it).second;
		imageJSON["tags"] = m_ImagesIdsTags.at((*it).first);

		imagesToJSON.push_back(imageJSON);
	}

	nlohmann::json index;
	index["images"] = imagesToJSON;

	JSONExporter jExporter;
	jExporter.exportJSON(index, "indexLibrary");

}


VectorImage * getRandomVectorImage() const {
	
}
