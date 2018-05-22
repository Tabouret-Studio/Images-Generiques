//  Created by Marie-Lou Barbier on 19/01/2018.


#include "IndexEngine.hpp"

#include "Core/AppObject.hpp"
#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"
#include "Engines/RessourcesEngine/Importers/JSONImporter.hpp"
#include "Engines/RessourcesEngine/Importers/SVGImporter.hpp"
#include "Engines/RessourcesEngine/Exporters/JSONExporter.hpp"
#include "Utils/Utils.hpp"

#ifdef __WIN32__

#else
	#include <dirent.h>
#endif

#include <fstream>
#include <algorithm>
#include <ctime>

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

	// Get Source folder
	//char const * sourceFolderPath = tinyfd_selectFolderDialog("sources directory", NULL);

	//if(!sourceFolderPath)
		m_sourcesPath = App->getAppPath() + "indexLibrary/sources/";
//	else
//		m_sourcesPath = std::string(sourceFolderPath);

	parseSVGSources();
}


void IndexEngine::parseSVGSources() {
#ifdef __WIN32__

	std::cout << "The source directory could not be parsed.\nImpossible to load SVG sources." << std::endl;

#else

	DIR *dir;
	struct dirent *ent;

	std::string path = m_sourcesPath;
	
	if((dir = opendir(path.c_str())) == NULL)
	{
		std::cout << "IndexLibrary folder could not be parsed.\nImpossible to load source files." << std::endl;
		return;
	} 

	while((ent = readdir(dir)) != NULL)
	{
		std::string srcFileName = ent->d_name;

		if(srcFileName.size() < 4)
			continue;

		if(srcFileName.substr(srcFileName.length() - 4, std::string::npos) != ".svg")
		{
			continue; // ignore non-SVG files
		}
			
		//srcFileName = srcFileName.substr(0, srcFileName.length() - 4);

		m_sources.push_back(srcFileName);
		
	}

	closedir(dir);

#endif
}


std::string IndexEngine::buildPath(const std::string &imgPath) const{
	return "indexLibrary/sources/"+imgPath;
}


VectorImage * IndexEngine::getVectorImage(const std::string fileName) const
{
	SVGImporter importer;
	return (VectorImage *)importer.getAsset(m_sourcesPath + fileName);
}


VectorImage * IndexEngine::getRandomVectorImage()
{
	parseSVGSources();
	int randomIndex = Utils::rand((int)m_sources.size());
	std::string randomFileName = m_sources[randomIndex];

	return getVectorImage(randomFileName);
}


void IndexEngine::exportVectorImage(VectorImage * image)
{
	SVGExporter exporter;
	std::string imgFileName = std::to_string(std::time(0));
	std::string exportPath = "exports/" + imgFileName;

	exporter.exportSVG(image, imgFileName);
}
