//
//  Mesh.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 20/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Mesh.hpp"

#include "Core/AppObject.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Utils/ShaderProgram.hpp"

Mesh::Mesh(const std::vector<Vertex> vertexList):
	Asset(MESH),
	m_vertexList(vertexList),
	m_vertexCount((uint)vertexList.size()),
	m_textureID(0),
	m_program(App->getDefaultProgram()),
	m_renderFormat(GL_TRIANGLES) {}

Mesh::Mesh():
	Asset(MESH),
	m_vertexList(),
	m_vertexCount(0),
	m_textureID(0),
	m_program(App->getDefaultProgram()),
	m_renderFormat(GL_TRIANGLES){}

void Mesh::appendVertex(const std::vector<Vertex> &vertexList)
{
	m_vertexList.insert(m_vertexList.end(), vertexList.begin(), vertexList.end());
}

void Mesh::appendVertex(const Vertex &vertex)
{
	m_vertexList.push_back(vertex);
}

void Mesh::generate()
{
	App->renderEngine->initVBO(this);

	App->renderEngine->initVAO(this);
}

void Mesh::applyCursor()
{
	Vertex temp;

	for(std::vector<Vertex>::iterator it = m_vertexList.begin(); it!= m_vertexList.end(); ++it)
	{
		temp = *it;

		temp.position = glm::vec3(glm::vec4((*it).position, 1) * m_cursor.getMatrix());
		temp.normal = glm::vec3(glm::vec4((*it).normal, 0) * m_cursor.getMatrix());

		*it = temp;
	}

	m_cursor.setMatrix(glm::mat4(1.0f));
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(2, &m_vao);
}
