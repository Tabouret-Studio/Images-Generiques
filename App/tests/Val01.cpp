//
//  Val01.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Val01.hpp"

namespace Tests
{
	//////////////
	// This is executed only one time at start up
	///////////
	void Val01::setup()
	{
		App->renderEngine->setShader("point");

		//Load SVG
		Utils::NSVG svg = Utils::NSVG("Assets/SVG/ml.svg");
		//std::cout << "size: " << m_image->width << " x " << m_image->height << std::endl;

		// Delete
		//nsvgDelete(image);

		//Création d'un VBO
		glGenBuffers(1, &m_vbo);

		//Bindind du vbo sur la cible
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//Création d'un tableau de float pour stocker les points du VBO
		std::vector<Utils::Bezier> paths = svg.getAllPaths();
		std::vector<Vertex2DColor> vertices;
		std::vector<glm::vec2> pathPoints = svg.getAllPoints();
		m_points = pathPoints.size();

		for(int j = 0; j < pathPoints.size(); ++j)
		{
			vertices.push_back(Vertex2DColor(pathPoints[j]));
		}

		//Puis on envois les données à la CG
		glBufferData(GL_ARRAY_BUFFER, m_points * sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);

		//Débindind du vbo de la cible pour éviter de le remodifier
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Création du VAO
		glGenVertexArrays(1, &m_vao);

		//Binding du vao (un seul à la fois)
		glBindVertexArray(m_vao);

		//Dire à OpenGL qu'on utilise le VAO
		const GLuint VERTEX_ATTR_POSITION = 1;
		const GLuint VERTEX_ATTR_COLOR = 2;
		glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

		//Indiquer à OpenGL où trouver les sommets
		//Bindind du vbo sur la cible
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//Spécification du format de l'attribut de sommet position
		glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), 0);
		glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), sizeof(glm::vec2));

		//Débindind du vbo de la cible pour éviter de le remodifier
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Débindind du vao de la cible pour éviter de le remodifier
		glBindVertexArray(0);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_POINT_SMOOTH);
	}


	//////////////
	// This is executed every frame
	///////////
	void Val01::render()
	{
		//On nettoit la fenêtre
		glClear(GL_COLOR_BUFFER_BIT);

		//On rebind le vao
		glBindVertexArray(m_vao);

		glDrawArrays(GL_POINTS, 0, m_points);

		//Débinding du vao de la cible pour éviter de le remodifier
		glBindVertexArray(0);
	}
}
