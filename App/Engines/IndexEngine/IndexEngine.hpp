//  Created by Marie-Lou Barbier on 19/01/2018.


#ifndef IndexEngine_hpp
#define IndexEngine_hpp

//////////////////////
//Forward declarations
class jsonObject;

//Get engine dependancies
#include "libraries.hpp"
#include "Elements/jsonObject.hpp"

#include <map>
//#include <vector>

//The engine
class IndexEngine
{
public:
	//Singleton
	static void instanciate();

	/**
	 * Browse the "sources" directory to register each SVG image
	 * Fill a map which linking an image unique_ID to its path 
	 */
	void parseSVGSources();
	
	VectorImage * getVectorImage(const std::string fileName) const;
	
	VectorImage * getRandomVectorImage();

	void exportVectorImage(VectorImage * image);

	///////
	//Utils

	
private:
	//Singleton
	static bool m_instanciated;

	//Constructor
	IndexEngine();
	~IndexEngine();

	//Fields
	std::string m_sourcesPath = "indexLibrary/sources/";
	std::vector<std::string> m_sources;

	std::string buildPath(const std::string &imgPath) const;
	
};

#endif /* IndexEngine_hpp */
