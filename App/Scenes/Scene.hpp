//
//  Scene.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 19/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include "libraries.hpp"
#include "Core/AppObject.hpp"

class Scene
{
public:

	////////
	//BASICS

	///Basic methods needs to be implemented by the scene, even if they may be empty.
	///Those methods may be called at any time, and need to be accessible

	/**
	 Fast-forward method to instanciate, init and in the scene App
	 */
	static void load();

	/**
	 Initialize the scene
	 */
	virtual void init() = 0;

	/**
	 Execute all the actions in the scene
	 */
	virtual void execute() = 0;

	/**
	 Render the scene on the screen
	 */
	virtual void render() = 0;

	/**
	 Destructor, used to properly free all the memory used by the scene
	 */
	virtual ~Scene() {}

	////////
	//EVENTS

	/// Collection of methods called after specific events
	/// Those methods are empty by default, you can implement them if you need to.

	/**
	 Called when the windows is resized
	 */
	virtual void onWindowResized() {};

	///////
	//UTILS

	/// Those methods are defined here and do not need to be implemented in the scenes
	/// It is although possible to do it if needed

	/**
	 Enable the scene
	 */
	virtual inline void enable()  { m_enable = true; };

	/**
	 Disable the scene
	 */
	virtual inline void disable() { m_enable = false; };

	/**
	 Tell if the scene is enabled or not

	 @return True if enabled, false otherwise
	 */
	virtual inline bool isEnabled() const { return m_enable; };

	/**
	 Return the unique ID of the scene

	 @return UUID
	 */
	virtual inline boost::uuids::uuid getUUID() const { return m_sceneID; };

	////////////////////////////
	//The *DO NOT TOUCH* section

	/// Main constructors & operator
	/// Do not modify this section because your scene "need it".
	/// If it needs it, you're doing it wrong

	/**
	 Scene constructor, generate the scene UUID
	 */
	Scene():m_sceneID(App->genUUID()) {}

	/**
	 Comparison operator for the scenes
	 Two scenes are equals if they have the same UUID.

	 @return True if the scenes are the same
	 */
	bool operator == (Scene * scene)
	{
		return getUUID() == scene->getUUID();
	};

protected:

	bool m_enable = true;

private:

	boost::uuids::uuid m_sceneID;
};

//TestScenes
#include "Val01.hpp"
#include "Val02.hpp"
#include "ml1.hpp"
#include "ml2.hpp"
#include "Gen01.hpp"


#include "ProtocolsMenu.hpp"
#include "ProtocolRenderer.hpp"

#include "AssemblageInterface.hpp"
#include "SimpleRenderer.hpp"
#include "AddInstructionInterface.hpp"

#endif /* Scene_h */
