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
	m_window = new glimac::SDLWindowManager(800, 600, "Images Génériques");

    // Initialize glew for OpenGL3+ support
	glewExperimental = GL_TRUE;
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

void RenderEngine::setShader(const std::string &shaderName)
{
	//Shader loading
	glimac::FilePath applicationPath(App->getAppPath().c_str());

	std::string VS = "Assets/Shaders/" + shaderName + ".vs.glsl";
	std::string FS = "Assets/Shaders/" + shaderName + ".fs.glsl";

	//Different loading path on macOS because of reasons
	#if __APPLE__
		glimac::Program program = glimac::loadProgram(VS, FS);
	#else
		glimac::Program program = glimac::loadProgram(applicationPath.dirPath() + VS,
													  applicationPath.dirPath() + FS);
	#endif

	program.use();
}



