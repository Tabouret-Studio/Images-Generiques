//
//  Bezier.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 11/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Bezier_hpp
#define Bezier_hpp

#include "../main.hpp"

namespace Utils
{
	class Bezier
	{
	public:
		Bezier(float startX, float startY,
			   float startHX, float startHY,
			   float endHX, float endHY,
			   float endX, float endY):
		m_startPoint(glm::vec2(startX, startY)),
		m_startHandle(glm::vec2(startHX, startHY)),
		m_endHandle(glm::vec2(endHX, endHY)),
		m_endPoint(glm::vec2(endX, endY)) {};

		Bezier(glm::vec2 startPoint, glm::vec2 startHandle,
			   glm::vec2 endHandle, glm::vec2 endPoint):
		m_startPoint(startPoint),
		m_startHandle(startHandle),
		m_endHandle(endHandle),
		m_endPoint(endPoint) {};

		std::vector<glm::vec2> getPoints(uint pointCount);

	private:
		glm::vec2 m_startPoint;
		glm::vec2 m_startHandle;
		glm::vec2 m_endHandle;
		glm::vec2 m_endPoint;

		glm::vec2 getIPointBetween(glm::vec2 A, glm::vec2 B, float coef);
	};
}

#endif /* Bezier_hpp */
