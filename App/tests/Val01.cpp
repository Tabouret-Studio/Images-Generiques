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

		//Création d'un tableau de float pour stocker les points du VBO
		std::vector<Vertex2DColor> vertices;
		std::vector<glm::vec2> pathPoints = svg.getAllPoints();
		m_points = pathPoints.size();

		for(int j = 0; j < pathPoints.size(); ++j)
		{
			vertices.push_back(Vertex2DColor(pathPoints[j]));
		}

		m_vbo = GL::buildVBO<Vertex2DColor>(vertices);
		m_vao = GL::buildVAO(m_vbo);

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
