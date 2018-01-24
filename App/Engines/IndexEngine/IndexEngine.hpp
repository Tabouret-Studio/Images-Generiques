#ifndef IndexEngine_hpp
#define IndexEngine_hpp

//////////////////////
//Forward declarations
class jsonObject;

//Get engine dependancies
#include "libraries.hpp"
#include "Engines/RessourcesEngine/Elements/jsonObject.hpp"

#include <map>
//#include <vector>

//The engine
class IndexEngine
{
public:
	//Singleton
	static void instanciate();

	void loadJSON();
	void readJSON();
	void writeJSON();

	/**
	 * Browse a jsonObject to get each image path
	 * Fill a map which linking an image unique_ID to its path
	 * 
	 * @param the json jsonObject used for indexation
	 */
	void getImagesIdsPaths(jsonObject * jsonObj);

	/**
	 * Browse a jsonObject to get each image tags
	 * Fill a map which linking an image unique_ID to a vector of tags
	 * 
	 * @param the json jsonObject used for indexation
	 */
	void getImagesIdsTages(jsonObject &jsonObj);

	///////
	//Utils

	
private:
	//Singleton
	static bool m_instanciated;

	//Constructor
	IndexEngine();
	~IndexEngine();

	//Fields
	std::map<srcId, std::string> m_ImagesIdsPaths;
	std::map<srcId, std::vector<std::string>> m_ImagesIdsTags;
};

#endif /* IndexEngine_hpp */