#include "IndexEngine.hpp"

#include "Core/AppObject.hpp"

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
IndexEngine::IndexEngine() {}


void IndexEngine::setImagesIdsPaths(jsonObject * jsonObj) {

	nlohmann::json * j = jsonObj->get();

	for(nlohmann::json::iterator it = (*j)["index"].begin(); it != (*j).end(); ++it)
	{
		std::cout << it.key() << " : " << it.value() << std::endl;

		srcId imgId= App->genUUID();
		std::string URL = it.value()["URL"];

		m_ImagesIdsPaths.insert(std::pair<srcId, std::string>(imgId, URL));
	}
}

void IndexEngine::setImagesIdsTages(jsonObject &jsonObj) {

}