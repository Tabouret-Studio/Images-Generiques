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
    RenderEngine::instanciate();
    
    App->renderEngine->init();
}

//The main loop
void Core::main()
{
	Tests::Test * currentTest = new Tests::TESTCLASS();

	currentTest->setup();

	//Used to set FPS
	std::chrono::high_resolution_clock::time_point start, end;

	while(App->isRunning())
	{
		////////////////////////////////
		//The main loop

		start = std::chrono::high_resolution_clock::now();

		App->renderEngine->pollEvents();

		currentTest->render();

		App->renderEngine->swapBuffers();

		end = std::chrono::high_resolution_clock::now();

		//Tempo
		Core::tempo(start, end);

		//
		/////////////////////////////////
	}

	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}
