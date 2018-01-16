//
//  Bezier.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 11/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Bezier.hpp"

#include <iostream>

std::vector<glm::vec2> Bezier::getPoints(const uint &pointCount) const
{
	std::vector<glm::vec2> vertices;

	float step = 1.f / (float)pointCount;

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

double Bezier::getLength()
{
	double t;
	glm::vec2 dot;
	glm::vec2 previous_dot;
	double length = 0.0;

	uint steps = 150;
	float stepsCoef = 100.f / steps;

	for (uint i = 0; i <= steps; i++)
	{
		previous_dot = dot;

		dot = getPoint((float) i * stepsCoef);

		if(i == 0)
			continue;

		length += glm::length(dot - previous_dot);
		//std::cout << "dist" << glm::length(dot - previous_dot) << std::endl;

		glm::vec2 distP = dot - previous_dot;
		float dist = sqrt(distP.x * distP.x + distP.y * distP.y);

		//std::cout << glm::to_string(dot) << glm::to_string(previous_dot) << std::endl;
		//std::cout << "dist" << dist << std::endl;
	}

	return length;
}
