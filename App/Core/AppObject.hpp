//
//  AppObject.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef AppObject_hpp
#define AppObject_hpp

#include <iostream>

//Forward declarations
class AppEngine;
class RenderEngine;

class AppObject
{
public:

	/**
	 Create the global App object as a singleton

	 @return true on success, false otherwise
	 */
	static bool instanciate();

	//Engines
	AppEngine * appEngine;
    RenderEngine * renderEngine;

	//App States
	/**
	 Tell if the app is currently running

	 @return true if yes, false otherwise
	 */
	bool isRunning();

	/**
	 Properly terminate the different components of the app
	 */
	void endApp();

private:
	//Singleton
	AppObject();
	static bool m_instanciated;

	//App status
	bool m_running;
};

extern AppObject * App;

#endif /* AppObject_hpp */
