//
//  Core.cpp
//  Music Composer
//
//  Created by Valentin Dufois on 21/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "../main.hpp"

//Ignite the different aspects of the game
void Core::ignite()
{
    //INIT ENGINES
	AppObject::instanciate();
    AppEngine::instanciate();
}

//The main loop
void Core::main()
{
	while(App->isRunning())
	{
		////////////////////////////////
		//The main loop

		std::cout << "-----------" << std::endl;
		std::cout << "Hello world" << std::endl;
		std::cout << "-----------" << std::endl;

		//Quit
		App->endApp();

		//
		/////////////////////////////////
	}
}
