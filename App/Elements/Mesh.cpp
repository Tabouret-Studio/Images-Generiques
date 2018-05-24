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

Mesh::Mesh():
	Asset(MESH),
	m_vertexList(),
	m_generated(false),
	m_boundsMin(glm::vec3(0)),
	m_boundsMax(glm::vec3(0)),
	m_textureID(0),
	m_program(App->getDefaultProgram()),
	m_renderFormat(GL_TRIANGLES) {}

Mesh::Mesh(const std::vector<Vertex> vertexList):
	Asset(MESH),
	m_vertexList(vertexList),
	m_generated(false),
	m_textureID(0),
	m_program(App->getDefaultProgram()),
	m_renderFormat(GL_TRIANGLES)
{
	calculateBoundaries();
}


glm::vec3 Mesh::getDimensions() const
{
	return glm::vec3(m_boundsMax.x - m_boundsMin.x, m_boundsMax.y - m_boundsMin.y, m_boundsMax.z - m_boundsMin.z);
}

void Mesh::fillVertex(const std::vector<Vertex> &vertexList)
{
	m_vertexList = vertexList;
	calculateBoundaries();
}

void Mesh::setTexture(const GLuint &textureID, const bool &toFree)
{
	m_textureID = textureID;
	m_freeTexture = toFree;
}

void Mesh::generate()
{
	deleteBuffers();

	App->renderEngine->initVBO(this);
	App->renderEngine->initVAO(this);

	m_generated = true;
}

void Mesh::applyCursor()
{
	if(m_cursor == glm::mat4(1.0))
		return;

	Vertex temp;

	for(std::vector<Vertex>::iterator it = m_vertexList.begin(); it!= m_vertexList.end(); ++it)
	{
		(*it).position = glm::vec3(m_cursor.getMatrix() * glm::vec4((*it).position, 1));
		(*it).normal = glm::vec3(m_cursor.getMatrix() * glm::vec4((*it).normal, 0));
	}

	m_cursor.setMatrix(glm::mat4(1.0f));

	calculateBoundaries();
}

void Mesh::setColor(const glm::vec4 &color)
{
	for(std::vector<Vertex>::iterator it = m_vertexList.begin(); it!= m_vertexList.end(); ++it)
		(*it).color = color;
}

void Mesh::render() const
{
	App->renderEngine->render(this, &m_cursor);
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
	updateBoundaries(vertexList);
	m_vertexList.insert(m_vertexList.end(), vertexList.begin(), vertexList.end());

	return *this;
}

Mesh &Mesh::operator <<(const Vertex &vertex)
{
	updateBoundaries({vertex});
	m_vertexList.push_back(vertex);

	return *this;
}

Mesh &Mesh::operator <<(const Mesh * mesh)
{
	Mesh meshVal = *mesh;
	meshVal.applyCursor();

	updateBoundaries(meshVal.m_vertexList);
	m_vertexList.insert(m_vertexList.end(), meshVal.m_vertexList.begin(), meshVal.m_vertexList.end());

	return *this;
}

void Mesh::freeTexture()
{
	glDeleteTextures(1, &m_textureID);
}

Mesh::~Mesh()
{
	deleteBuffers();
	if(m_freeTexture)
		freeTexture();
}

void Mesh::calculateBoundaries()
{
	if(m_vertexList.size() == 0)
		return;

	m_boundsMin = m_vertexList[0].position;
	m_boundsMax = m_vertexList[0].position;

	for(const Vertex &vertex : m_vertexList)
	{
		//Min
		if(vertex.position.x < m_boundsMin.x) m_boundsMin.x = vertex.position.x;
		if(vertex.position.y < m_boundsMin.y) m_boundsMin.y = vertex.position.y;
		if(vertex.position.z < m_boundsMin.z) m_boundsMin.z = vertex.position.z;

		//Max
		if(vertex.position.x > m_boundsMax.x) m_boundsMax.x = vertex.position.x;
		if(vertex.position.y > m_boundsMax.y) m_boundsMax.y = vertex.position.y;
		if(vertex.position.z > m_boundsMax.z) m_boundsMax.z = vertex.position.z;
	}
}

void Mesh::updateBoundaries(const std::vector<Vertex> &newVertex)
{
	if(newVertex.size() == 0)
		return;

	for(const Vertex &vertex : newVertex)
	{
		//Min
		if(vertex.position.x < m_boundsMin.x) m_boundsMin.x = vertex.position.x;
		if(vertex.position.y < m_boundsMin.y) m_boundsMin.y = vertex.position.y;
		if(vertex.position.z < m_boundsMin.z) m_boundsMin.z = vertex.position.z;

		//Max
		if(vertex.position.x > m_boundsMax.x) m_boundsMax.x = vertex.position.x;
		if(vertex.position.y > m_boundsMax.y) m_boundsMax.y = vertex.position.y;
		if(vertex.position.z > m_boundsMax.z) m_boundsMax.z = vertex.position.z;
	}
}
