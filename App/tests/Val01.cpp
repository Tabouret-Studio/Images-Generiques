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
	void Val01::setup()
	{
		App->renderEngine->setShader("point");

		//Load SVG
		m_image = nsvgParseFromFile("Assets/SVG/ml.svg", "px", 96);
		std::cout << "size: " << m_image->width << " x " << m_image->height << std::endl;

		// Delete
		//nsvgDelete(image);

		//Création d'un VBO
		glGenBuffers(1, &m_vbo);

		//Bindind du vbo sur la cible
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//Création d'un tableau de float pour stocker les points du VBO
		std::vector<Vertex2DColor> vertices;
		m_points = 0;

		// Parse SVG
		for (NSVGshape * shape = m_image->shapes; shape != NULL; shape = shape->next)
		{
			for (NSVGpath * path = shape->paths; path != NULL; path = path->next)
			{
				for (int i = 0; i < path->npts-1; i += 3) {

					float * p = &path->pts[i * 2];

//					x = (p[0] / 1000.f) - .5f,
//					y = ((p[1] / 1000.f) - .5f) * -1;
//					vertices.push_back(Vertex2DColor(glm::vec2(x, y), glm::vec3(0, 0, 0)));
//
//					/*x = (p[2] / 1000.f) - .5f;
//					y = ((p[3] / 1000.f) - .5f) * -1;
//					vertices.push_back(Vertex2DColor(glm::vec2(x, y), glm::vec3(0, 0, 0)));*/
//
//					/*x = (p[4] / 1000.f) - .5f;
//					y = ((p[5] / 1000.f) - .5f) * -1;
//					vertices.push_back(Vertex2DColor(glm::vec2(x, y), glm::vec3(0, 0, 0)));*/
//
//					x = (p[6] / 1000.f) - .5f;
//					y = ((p[7] / 1000.f) - .5f) * -1;
//					vertices.push_back(Vertex2DColor(glm::vec2(x, y), glm::vec3(0, 0, 0)));

					glm::vec2 startP = glm::vec2((p[0] / 500.f) - 1.f, ((p[1] / 375.f) - 1.f) * -1);
					glm::vec2 startH = glm::vec2((p[2] / 500.f) - 1.f, ((p[3] / 375.f) - 1.f) * -1);
					glm::vec2 endH = glm::vec2((p[4] / 500.f) - 1.f, ((p[5] / 375.f) - 1.f) * -1);
					glm::vec2 endP = glm::vec2((p[6] / 500.f) - 1.f, ((p[7] / 375.f) - 1.f) * -1);

					Utils::Bezier pathBezier = Utils::Bezier(startP, startH, endH, endP);

					std::vector<glm::vec2> pathPoints = pathBezier.getPoints(150);
					m_points += pathPoints.size();

					for(int j = 0; j < pathPoints.size(); ++j)
					{
						vertices.push_back(Vertex2DColor(pathPoints[j], glm::vec3(0, 0, 0)));
					}
//					std::cout << "point coords : " << x << " " << y << std::endl;
				}
			}
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
		glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

		//Indiquer à OpenGL où trouver les sommets
		//Bindind du vbo sur la cible
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//Spécification du format de l'attribut de sommet position
		glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), 0);

		//Débindind du vbo de la cible pour éviter de le remodifier
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Débindind du vao de la cible pour éviter de le remodifier
		glBindVertexArray(0);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_POINT_SMOOTH);
	}

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
