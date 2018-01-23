#ifndef IndexEngine_hpp
#define IndexEngine_hpp

//////////////////////
//Forward declarations


//Get engine dependancies
#include "libraries.hpp"

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

	///////
	//Utils

	
private:
	//Singleton
	static bool m_instanciated;

	//Constructor
	IndexEngine();
	~IndexEngine();

	//Fields
	std::map<std::string, srcId> m_ImageIdsPaths;
	std::map<srcId, std::vector<std::string>> m_ImageIdsTags;
};

#endif /* IndexEngine_hpp */