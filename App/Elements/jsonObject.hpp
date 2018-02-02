#ifndef jsonObject_hpp
#define jsonObject_hpp

#include "libraries.hpp"
#include "Engines/RessourcesEngine/RessourcesEngine.hpp"
#include "Asset.hpp"

#include <iostream>
#include <vector>

class jsonObject : public Asset
{
public:

	//Constructors
	jsonObject(): Asset(JSON), m_json(new nlohmann::json) {};
	jsonObject(nlohmann::json * j): Asset(JSON), m_json(j) {};

	inline nlohmann::json * get() { return m_json; }

	~jsonObject() { delete m_json; };

private:
	nlohmann::json * m_json;

};

#endif /* jsonObject_hpp */
