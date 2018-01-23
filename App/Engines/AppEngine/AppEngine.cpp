//
//  GameEngine.cpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "libraries.hpp"

#include "AppEngine.hpp"
#include "Core/AppObject.hpp"
#include "Scenes/Scene.hpp"

#include "Engines/RenderEngine/RenderEngine.hpp"

bool AppEngine::m_instanciated = false;

/**
 * Instanciate the engine as a Singleton
 */
void AppEngine::instanciate()
{
    if(m_instanciated)
        return;
    
    App->appEngine = new AppEngine();
    
    m_instanciated = true;
}

AppEngine::AppEngine() {}

void AppEngine::executeScenes()
{
	//Update events
	parseEvents();

	//get all scenes
	std::vector<Scene *> scenes = App->getScenes();

	//Execute all scenes
	for(std::vector<Scene *>::iterator it = scenes.begin(); it != scenes.end(); ++it)
	{
		if((*it)->isEnabled()) {
			(*it)->execute();
		}
	}
}

void AppEngine::renderScenes()
{
	/*Clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//get all scenes
	std::vector<Scene *> scenes = App->getScenes();

	//Render all scenes
	for(std::vector<Scene *>::iterator it = scenes.begin(); it != scenes.end(); ++it)
	{
		if((*it)->isEnabled()) {
			(*it)->render();
		}
	}

	//Swap buffers
	SDL_GL_SwapWindow(App->mainWindow);
}
