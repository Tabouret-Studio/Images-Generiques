#ifndef JSON_hpp
#define JSON_hpp

//////////////////////
//Forward declarations
class nlohmann::json;

#include "Asset.hpp"

#include <iostream>
#include <vector>


class JSON : public Asset
{
public:

	//Constructors
	JSON(nlohmann::json * j) {}

	inline nlohmann::json * get() { return m_json; }

private:
	nlohmann::json * m_json;

};

#endif /* JSON_hpp */
