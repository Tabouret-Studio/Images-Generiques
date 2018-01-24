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
	m_generated(false),
	m_textureID(0),
	m_program(App->getDefaultProgram()),
	m_renderFormat(GL_TRIANGLES) {}

Mesh::Mesh():
	Asset(MESH),
	m_vertexList(),
	m_vertexCount(0),
	m_generated(false),
	m_textureID(0),
	m_program(App->getDefaultProgram()),
	m_renderFormat(GL_TRIANGLES){}

void Mesh::generate()
{
	deleteBuffers();

	App->renderEngine->initVBO(this);
	App->renderEngine->initVAO(this);

	m_generated = true;
}

void Mesh::applyCursor()
{
	Vertex temp;

	for(std::vector<Vertex>::iterator it = m_vertexList.begin(); it!= m_vertexList.end(); ++it)
	{
		(*it).position = glm::vec3(m_cursor.getMatrix() * glm::vec4((*it).position, 1));
		(*it).normal = glm::vec3(m_cursor.getMatrix() * glm::vec4((*it).normal, 0));
	}

	m_cursor.setMatrix(glm::mat4(1.0f));
}

void Mesh::render() const
{
	App->renderEngine->render(this, &m_cursor);
}

void Mesh::freeTexture()
{
	glDeleteTextures(1, &m_textureID);
}

Mesh::~Mesh()
{
	deleteBuffers();
}

void Mesh::deleteBuffers()
{
	if(m_generated)
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
		m_generated = false;
	}
}

Mesh &Mesh::operator <<(const std::vector<Vertex> &vertexList)
{
	m_vertexList.insert(m_vertexList.end(), vertexList.begin(), vertexList.end());
	return *this;
}

Mesh &Mesh::operator <<(const Vertex &vertex)
{
	m_vertexList.push_back(vertex);
	return *this;
}

Mesh &Mesh::operator <<(const Mesh * mesh)
{
	Mesh meshVal = *mesh;
	meshVal.applyCursor();

	m_vertexList.insert(m_vertexList.end(), meshVal.m_vertexList.begin(), meshVal.m_vertexList.end());
	return *this;
}
