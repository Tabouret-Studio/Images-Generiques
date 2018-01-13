//
//  AppObject.cpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "AppObject.hpp"
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
		if((*it) == scene)
		{
			delete (*it);
			m_scenes.erase(it);
			return;
		}
	}
}
