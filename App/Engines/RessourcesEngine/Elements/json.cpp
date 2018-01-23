#include "JSON.hpp"

#include "Core/AppObject.hpp"
#include "Engines/IndexEngine/IndexEngine.hpp"

#include "libraries.hpp"


	JSON(nlohmann::json j) : m_json(j) {}
