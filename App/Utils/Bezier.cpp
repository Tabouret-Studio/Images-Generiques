//
//  Bezier.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 11/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "../main.hpp"

namespace Utils
{
	std::vector<glm::vec2> Bezier::getPoints(uint pointCount)
	{
		std::vector<glm::vec2> vertices;

		float step = 1.f / (float)pointCount;

		for(float i = 0 ; i < 1 ; i += step)
		{
			//External references
			glm::vec2 refA = getIPointBetween(m_startPoint, m_startHandle, i);
			glm::vec2 refB = getIPointBetween(m_startHandle, m_endHandle, i);
			glm::vec2 refC = getIPointBetween(m_endHandle, m_endPoint, i);

			//Internal references-
			glm::vec2 internA = getIPointBetween(refA, refB, i);
			glm::vec2 internB = getIPointBetween(refB, refC, i);

			//Interpolated point
			glm::vec2 point = getIPointBetween(internA, internB, i);

			vertices.push_back(point);
		}

		return vertices;
	}

	glm::vec2 Bezier::getIPointBetween(glm::vec2 A, glm::vec2 B, float coef)
	{
		return A + ((B - A) * coef);
	}
}
