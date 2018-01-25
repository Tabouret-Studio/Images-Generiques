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
	 * Browse a jsonObject to get each image path
	 * Fill a map which linking an image unique_ID to its path 
	 */
	void loadLibrary();

	std::vector<srcId> * getImagesIds() const;
	VectorImage * getVectorImage(const srcId &imgId) const;
	std::vector<std::string> getImageTags(const srcId &imgId) const;
	void insertVectorIMage(const VectorImage * image, const std::vector<std::string> &tags);
	void exportIndexToJSON() const;
	///////
	//Utils

	
private:
	//Singleton
	static bool m_instanciated;

	//Constructor
	IndexEngine();
	~IndexEngine();


	bool imageIdIsValid(const srcId &imgId) const;

	//Fields
	std::map<srcId, std::string> m_ImagesIdsPaths;
	std::map<srcId, std::vector<std::string>> m_ImagesIdsTags;
};

#endif /* IndexEngine_hpp */