#include "IndexEngine.hpp"

#include "Core/AppObject.hpp"

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
IndexEngine::IndexEngine() {}

