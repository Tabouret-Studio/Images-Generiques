//
//  RenderEngine.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 09/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "../../main.hpp"

bool RenderEngine::m_instanciated = false;

/**
 * Instanciate the engine as a Singleton
 */
void RenderEngine::instanciate()
{
    if(m_instanciated)
        return;
    
    App->renderEngine = new RenderEngine();
    
    m_instanciated = true;
}

RenderEngine::RenderEngine() {}

void RenderEngine::init()
{
    // Initialize SDL and open a window
	m_window = new glimac::SDLWindowManager(800, 600, "GLImac");
    
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        throw std::runtime_error("Glew init error.");
    }
    
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
}

void RenderEngine::swapBuffers()
{
	m_window->swapBuffers();
}

void RenderEngine::pollEvents()
{
	SDL_Event e;
	while(m_window->pollEvent(e)) {
		if(e.type == SDL_QUIT) {
			App->endApp();
		}
	}
}
