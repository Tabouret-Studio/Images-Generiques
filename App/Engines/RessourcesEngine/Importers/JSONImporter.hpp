#ifndef JSONImporter_hpp
#define JSONImporter_hpp

//Forward declaration


#include "Importer.hpp"

/**
 Import json file (JSON)
 */
class JSONImporter: public Importer
{
public:
		Asset * getAsset(const std::string &path);

private:
};

#endif /* JSONImporter_hpp */
