#ifndef JSON_hpp
#define JSON_hpp

//////////////////////
//Forward declarations

#include "Engines/RessourcesEngine/RessourcesEngine.hpp"
#include "Asset.hpp"

#include <iostream>
#include <vector>


class jsonObject : public Asset
{
public:

	//Constructors
	jsonObject(nlohmann::json * j) : Asset(JSON), m_json(j) {}

	inline nlohmann::json * get() { return m_json; }

private:
	nlohmann::json * m_json;

};

#endif /* JSON_hpp */
