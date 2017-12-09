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

	while(App->isRunning())
	{
		////////////////////////////////
		//The main loop

		App->renderEngine->pollEvents();

		renderer();

		App->renderEngine->swapBuffers();

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
	//Création d'un VBO
	glGenBuffers(1, &m_vbo);

	//Bindind du vbo sur la cible
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	GLfloat vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
	//Puis on envois les données à la CG
	glBufferData(GL_ARRAY_BUFFER, 6*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	//Débindind du vbo de la cible pour éviter de le remodifier
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Création du VAO
	glGenVertexArrays(1, &m_vao);

	//Binding du vao (un seul à la fois)
	glBindVertexArray(m_vao);

	//Dire à OpenGL qu'on utilise le VAO
	const GLuint VERTEX_ATTR_POSITION = 0;
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

	//Indiquer à OpenGL où trouver les sommets
	//Bindind du vbo sur la cible
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//Spécification du format de l'attribut de sommet position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
	//Débinding du vbo de la cible pour éviter de le remodifier
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

	//On dessine le triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Débindind du vao de la cible pour éviter de le remodifier
	glBindVertexArray(0);
}
