//
//  AppObject.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef AppObject_hpp
#define AppObject_hpp

//Forward declarations
class AppEngine;
class RessourcesEngine;
class RenderEngine;
class Scene;
class ShaderProgram;

#include "libraries.hpp"

class AppObject
{
public:

	/**
	 Create the global App object as a singleton
	 */
	static void instanciate(const std::string &appPath);

	/**
	 Return the path to the app

	 @return The path
	 */
	inline std::string getAppPath() const { return m_appPath; }

	/////////
	//Engines
	AppEngine * appEngine;
	RessourcesEngine * ressourcesEngine;
	RenderEngine * renderEngine;

	////////////
	//SDL Window
	SDL_Window * mainWindow;

	/**
	 Get the window width

	 @return The window width
	 */
	inline uint getWidth() const { return m_width; };

	/**
	 Get the window height

	 @return The window heigth
	 */
	inline uint getHeight() const { return m_height; };

	/**
	 Set the windows width

	 @param width New window width
	 */
	inline void setWidth(const uint &width) { m_width = width; };

	/**
	 Set the windows height

	 @param height New window height
	 */
	inline void setHeigth(const uint &height) { m_height = height; };

	////////////
	//App States

	/**
	 Tell if the app is currently running

	 @return true if yes, false otherwise
	 */
	inline bool isRunning() const { return m_running; };

	/**
	 Properly terminate the different components of the app
	 */
	inline void endApp() { m_running = false; };

	////////
	//Scenes

	/**
	 Add a new scene to the loop
	 The scene must have been initialized

	 @param scene The scene to add
	 */
	inline void addScene(Scene * scene) { m_scenes.push_back(scene); };

	/**
	 Return all the scenes currently runnings

	 @return The scenes in a vector
	 */
	std::vector<Scene *> getScenes() const { return m_scenes; };

	/**
	 Remove the given scene from the loop
	 The scene is free-ed by this function

	 @param scene The scene to remove
	 */
	void removeScene(Scene * scene);

	////////
	//Shader

	/**
	 Return the default shader program

	 @return A ShaderProgram Object
	 */
	inline ShaderProgram * getDefaultProgram() { return m_defaultProgram; };

	/**
	 Set default shader program

	 @param prog A ShaderProgram
	 */
	inline void setDefaultProgram(ShaderProgram * prog) { m_defaultProgram = prog; };


	////////////
	//SCENE UUID
	inline boost::uuids::uuid genUUID() { return m_uuidGenerator(); };

private:
	//Singleton
	AppObject(const std::string &appPath):
		m_appPath(appPath) {};
	static bool m_instanciated;

	//App status
	bool m_running = true;
	std::string m_appPath;

	//window dimensions
	uint m_width;
	uint m_height;

	//Scenes
	std::vector<Scene *> m_scenes;

	//default shader
	ShaderProgram * m_defaultProgram;

	//UUID
	boost::uuids::random_generator m_uuidGenerator;
};

extern AppObject * App;

#endif /* AppObject_hpp */
