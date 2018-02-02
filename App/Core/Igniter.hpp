//
//  Igniter.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 21/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Igniter_hpp
#define Igniter_hpp

#include "libraries.hpp"

/**
 Instanciate the AppObject, engines, and start the window context.
 All initializations that should be performs only once in the app life must be called from here.
 */
class Igniter
{
public:
	/**
	 Instanciate the AppObject and the engines

	 @param appPath Path to the app executable
	 */
	void igniteAppObject(const std::string &appPath);

	/**
	 Start the SDL and create the window

	 @param width <#width description#>
	 @param height <#height description#>
	 */
	void igniteSDL(const uint &width, const uint &height);

	/**
	 Set up modern OpenGL and options
	 */
	void igniteOpenGL();

	/**
	 Ignite engines that need to perform operation after initializing OpenGL
	 */
	void igniteEngines();
};

#endif /* Igniter_hpp */
