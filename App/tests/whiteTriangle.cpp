//
//  whiteTriangle.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "whiteTriangle.hpp"

namespace Tests
{
	//////////////
	// This is executed only one time at start up
	///////////
	void whiteTriangle::setup()
	{
		App->renderEngine->setShader("triangle");

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
	void whiteTriangle::render()
	{
		//On nettoit la fenêtre
		glClear(GL_COLOR_BUFFER_BIT);

		//On rebind le vao
		glBindVertexArray(m_vao);

		//On dessine le triangle //3*N pour le nombre de sommets pour N triangles
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Débindind du vao de la cible pour éviter de le remodifier
		glBindVertexArray(0);
	}
}
