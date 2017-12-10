//
//  AppObject.cpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "../main.hpp"

//Singleton
AppObject * App = nullptr;
bool AppObject::m_instanciated = false;

bool AppObject::instanciate()
{
	if(m_instanciated)
		return false;

	App = new AppObject();

	return true;
}

AppObject::AppObject():
    appEngine(nullptr),
    m_running(true) {}

//App status Getter and manipulation
bool AppObject::isRunning()
{
	return m_running;
}

void AppObject::endApp()
{
	m_running = false;
}

void AppObject::setAppPath(const std::string &path)
{
	m_appPath = path;
}
