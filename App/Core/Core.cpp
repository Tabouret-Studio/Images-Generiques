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
	setup();

	//Used to set FPS
	std::chrono::high_resolution_clock::time_point start, end;

	while(App->isRunning())
	{
		////////////////////////////////
		//The main loop

		start = std::chrono::high_resolution_clock::now();

		App->renderEngine->pollEvents();

		renderer();

		//App->renderEngine->swapBuffers();

		end = std::chrono::high_resolution_clock::now();

		//Tempo
		Core::tempo(start, end);

		//
		/////////////////////////////////
	}

	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}


//////////////
// This is executed only one time at start up
///////////
void Core::setup()
{
	//Shader loading
	glimac::FilePath applicationPath(App->getAppPath().c_str());

	std::string VS = "Assets/Shaders/triangle.vs.glsl";
	std::string FS = "Assets/Shaders/triangle.fs.glsl";

	//Different loading path on macOS because of reasons
#if __APPLE__
	glimac::Program program = glimac::loadProgram(VS, FS);
#else
	Program program = loadProgram(applicationPath.dirPath() + VS,
								  applicationPath.dirPath() + FS);
#endif

	program.use();

	int N = 50;

	//Création d'un VBO
	glGenBuffers(1, &m_vbo);

	//Bindind du vbo sur la cible
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	//Création d'un tableau de float pour stocker les points du VBO
	GLfloat vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};

	//Puis on envois les données à la CG
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	//Débindind du vbo de la cible pour éviter de le remodifier
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Création du VAO
	glGenVertexArrays(1, &m_vao);

	//Binding du vao (un seul à la fois)
	glBindVertexArray(m_vao);

	//Dire à OpenGL qu'on utilise le VAO
	const GLuint VERTEX_ATTR_POSITION = 1;
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

	//Indiquer à OpenGL où trouver les sommets
	//Bindind du vbo sur la cible
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	//Spécification du format de l'attribut de sommet position
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

	//Débindind du vbo de la cible pour éviter de le remodifier
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Débindind du vao de la cible pour éviter de le remodifier
	glBindVertexArray(0);
}




//////////////
// This is executed every frame
///////////
void Core::renderer()
{
	//On nettoit la fenêtre
	glClear(GL_COLOR_BUFFER_BIT);

	//On rebind le vao
	glBindVertexArray(m_vao);

	//On dessine le triangle //3*N pour le nombre de sommets pour N triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Débindind du vao de la cible pour éviter de le remodifier
	glBindVertexArray(0);

	App->renderEngine->swapBuffers();
}
