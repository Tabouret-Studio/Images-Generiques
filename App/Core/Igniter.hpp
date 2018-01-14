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
	void igniteAppObject(const std::string &appPath);
	void igniteSDL(const uint &width, const uint &height);
	void igniteOpenGL();
	void igniteEngines();
};

#endif /* Igniter_hpp */
