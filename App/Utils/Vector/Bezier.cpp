//
//  Bezier.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 11/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Bezier.hpp"

#include "Engines/RessourcesEngine/Elements/Mesh.hpp"

#include <iostream>


void Bezier::setDimensions(const float &width, const float &height)
{
	m_dimensions = glm::vec2(width, height);
}

std::vector<glm::vec2> Bezier::getPoints(const float &precision) const
{
	std::vector<glm::vec2> vertices;
	uint pc;

	if(precision <= 0)
		return vertices;
	else if(precision <= 1)
		 pc = getLength() * 2.f * precision;
	else
		pc = precision;


	float step = 1.f / (float)pc;

	for(float i = 0 ; i < 1 ; i += step)
	{
		//External references
		vertices.push_back(getPoint(i));
	}

	return vertices;
}

glm::vec2 Bezier::getPoint(const float &percentage) const
{
	glm::vec2 refA = getIPointBetween(m_startPoint, m_startHandle, percentage);
	glm::vec2 refB = getIPointBetween(m_startHandle, m_endHandle, percentage);
	glm::vec2 refC = getIPointBetween(m_endHandle, m_endPoint, percentage);

	//Internal references-
	glm::vec2 internA = getIPointBetween(refA, refB, percentage);
	glm::vec2 internB = getIPointBetween(refB, refC, percentage);

	//Interpolated point
	return  getIPointBetween(internA, internB, percentage);
}

glm::vec2 Bezier::getIPointBetween(glm::vec2 A, glm::vec2 B, float coef) const
{
	return A + ((B - A) * coef);
}

float Bezier::getLength() const
{
	glm::vec2 dot;
	glm::vec2 previous_dot;
	double length = 0.0;

	uint steps = 150;
	float stepsCoef = (100.f / steps) / 100.f;

	for (uint i = 0; i <= steps; ++i)
	{
		previous_dot = dot;

		dot = getPoint((float) i * stepsCoef);

		if(i == 0)
			continue;

		length += glm::length(dot - previous_dot);
	}

	return length;
}

Mesh * Bezier::getMesh() const
{
	Mesh * mesh = new Mesh();

	std::vector<glm::vec2> points = getPoints();

	for(std::vector<glm::vec2>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		*mesh << Vertex(glm::vec3(*it, 0));
	}

	mesh->getCursor()->setMatrix(m_cursor);

	return mesh;
}

void Bezier::applyCursor(const DrawCursor * cursor)
{
	Vertex temp;

	m_startPoint = glm::vec2(cursor->getMatrix() * glm::vec4(m_startPoint, 0, 1));
	m_startHandle = glm::vec2(cursor->getMatrix() * glm::vec4(m_startHandle, 0, 1));
	m_endHandle = glm::vec2(cursor->getMatrix() * glm::vec4(m_endHandle, 0, 1));
	m_endPoint = glm::vec2(cursor->getMatrix() * glm::vec4(m_endPoint, 0, 1));

	m_dimensions = glm::vec2(cursor->getMatrix() * glm::vec4(m_dimensions, 0, 0));
}
