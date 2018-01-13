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
#include "Core/AppObject.hpp"

#include "Engines/AppEngine/AppEngine.hpp"
#include "Engines/RessourcesEngine/RessourcesEngine.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"

#include "Utils/FilePath.hpp"


class Igniter
{
public:
	void igniteAppObject(std::string appPath);
	void igniteSDL(float width, float height);
	void igniteOpenGL();
	void igniteEngines();
};

#endif /* Igniter_hpp */
