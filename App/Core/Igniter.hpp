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

	void igniteEngines();
};

#endif /* Igniter_hpp */
