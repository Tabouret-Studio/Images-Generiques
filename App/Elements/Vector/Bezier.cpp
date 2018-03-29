//
//  Bezier.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 11/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Bezier.hpp"

#include "Elements/Mesh.hpp"
#include "Utils/Utils.hpp"

#include <iostream>

std::vector<glm::vec3> Bezier::getPoints(const float &precision) const
{
	std::vector<glm::vec3> vertices;
	float pc;

	if(precision <= 0)
		return vertices;
	else if(precision <= 1)
		 pc = getLength() * 1.f * precision;
	else
		pc = precision;

	pc = std::min(pc, 400.0f);

	float step = 1.f / (float)pc;

	for(float i = 0 ; i < 1 ; i += step)
	{
		//External references
		vertices.push_back(getPoint(i));
	}

	//std::cout << pc << " - " << glm::length(m_endPoint - m_startPoint) << std::endl;

	return vertices;
}

glm::vec3 Bezier::getPoint(const float &percentage) const
{
	glm::vec3 refA = Utils::getIPointBetween(m_startPoint, m_startHandle, percentage);
	glm::vec3 refB = Utils::getIPointBetween(m_startHandle, m_endHandle, percentage);
	glm::vec3 refC = Utils::getIPointBetween(m_endHandle, m_endPoint, percentage);

	//Internal references-
	glm::vec3 internA = Utils::getIPointBetween(refA, refB, percentage);
	glm::vec3 internB = Utils::getIPointBetween(refB, refC, percentage);

	//Interpolated point
	return  Utils::getIPointBetween(internA, internB, percentage);
}

float Bezier::getLength() const
{
	glm::vec3 dot;
	glm::vec3 previous_dot;
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

Mesh * Bezier::getMesh(const float &precision) const
{
	Mesh * mesh = new Mesh();

	std::vector<glm::vec3> points = getPoints(precision);

	for(std::vector<glm::vec3>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		*mesh << Vertex(*it);
	}

	mesh->getCursor()->setMatrix(m_cursor);

	return mesh;
}

void Bezier::applyCursor(const glm::mat4 &shapeCursor)
{
	Vertex temp;

	m_startPoint = glm::vec3(shapeCursor * m_cursor.getMatrix() * glm::vec4(m_startPoint, 1));
	m_startHandle = glm::vec3(shapeCursor * m_cursor.getMatrix() * glm::vec4(m_startHandle, 1));
	m_endHandle = glm::vec3(shapeCursor * m_cursor.getMatrix() * glm::vec4(m_endHandle, 1));
	m_endPoint = glm::vec3(shapeCursor * m_cursor.getMatrix() * glm::vec4(m_endPoint, 1));

	m_boundsMin = glm::vec3(shapeCursor * m_cursor.getMatrix() * glm::vec4(m_boundsMin, 1));
	m_boundsMax = glm::vec3(shapeCursor * m_cursor.getMatrix() * glm::vec4(m_boundsMax, 1));

	m_cursor.reset();
}

void Bezier::move(const glm::vec3 &dest)
{
	glm::vec3 distanceVec = dest - m_startPoint;
	m_cursor.translate(distanceVec);
	applyCursor();
}

void Bezier::calculateBounds()
{
	//Calculate bezier coordinates
	std::vector<glm::vec3> points = getPoints();

	m_boundsMin = points[0];
	m_boundsMax = points[0];

	for(std::vector<glm::vec3>::const_iterator it = points.begin()+1; it != points.end(); ++it)
	{
		//Min
		if(it->x < m_boundsMin.x) m_boundsMin.x = it->x;
		if(it->y < m_boundsMin.y) m_boundsMin.y = it->y;
		if(it->z < m_boundsMin.z) m_boundsMin.z = it->z;

		//Max
		if(it->x > m_boundsMax.x) m_boundsMax.x = it->x;
		if(it->y > m_boundsMax.y) m_boundsMax.y = it->y;
		if(it->z > m_boundsMax.z) m_boundsMax.z = it->z;
	}
}
