//
//  AppObject.cpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Core/AppObject.hpp"

#include "Utils/ShaderProgram.hpp"
#include "Scenes/Scene.hpp"

//Singleton
AppObject * App = nullptr;
bool AppObject::m_instanciated = false;

void AppObject::instanciate(const std::string &appPath)
{
	if(m_instanciated) {
		return;
	}

	App = new AppObject(appPath + "/");

	m_instanciated = true;
}

//Scenes
void AppObject::removeScene(Scene * scene)
{
	for(std::vector<Scene *>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
	{
		if((*it) != scene)
			continue;

		delete (*it);
		(*it) = nullptr;
		m_scenes.erase(it);
		return;
	}
}

// Window
void AppObject::toggleFullScreen()
{
	if(m_windowIsFullScreen)
	{
		SDL_SetWindowFullscreen(mainWindow, 0);

		m_windowIsFullScreen = false;
		return;
	}

	SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);

	m_windowIsFullScreen = true;
}
