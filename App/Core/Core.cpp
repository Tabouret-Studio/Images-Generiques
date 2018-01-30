//
//  Core.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 21/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Core.hpp"

#include "AppObject.hpp"
#include "Igniter.hpp"
#include "Scenes/Scene.hpp"

#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

#include <thread>

//Ignite the different aspects of the game
void Core::ignite(std::string appPath)
{
	Igniter igniter = Igniter();

	igniter.igniteAppObject(appPath);
	igniter.igniteSDL(800, 600);
	igniter.igniteOpenGL();
	igniter.igniteEngines();
}

//The main loop
void Core::main()
{
	std::chrono::high_resolution_clock::time_point start, end;

	//////////////////////
	//Load the first scene
	Scenes::AlexGen01::load();
	//Scenes::ProtocolsMenu::load();

	while(App->isRunning())
	{
		////////////////////////////////
		//The main loop

		start = std::chrono::high_resolution_clock::now();

		//Actions
		App->appEngine->executeScenes();

		//Render
		App->appEngine->renderScenes();

		end = std::chrono::high_resolution_clock::now();

		//Tempo
		Core::tempo(start, end);

		//
		/////////////////////////////////
	}

	//End of game, clear everything
	//TODO
}

void Core::tempo(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end)
{
	std::chrono::milliseconds elapsed, toWait;

	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	if(elapsed.count() < FRAMERATE)
	{
		toWait = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(FRAMERATE) - elapsed);
		std::this_thread::sleep_for(toWait);
	}
}

