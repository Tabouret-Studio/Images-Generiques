//
//  Bezier.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 11/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Bezier_hpp
#define Bezier_hpp

#include "libraries.hpp"

class Bezier
{
public:
	/**
	 Build a Bezier curve

	 @param startX X position of the starting point
	 @param startY Y position of the starting point
	 @param startHX X position of the starting point handle
	 @param startHY Y position of the starting point handle
	 @param endHX X position of the ending point handle
	 @param endHY Y position of the ending point handle
	 @param endX X position of the ending point
	 @param endY Y position of the ending point handle
	 */
	Bezier(const float &startX, const float &startY,
		   const float &startHX, const float &startHY,
		   const float &endHX, const float &endHY,
		   const float &endX, const float &endY):
	m_startPoint(glm::vec2(startX, startY)),
	m_startHandle(glm::vec2(startHX, startHY)),
	m_endHandle(glm::vec2(endHX, endHY)),
	m_endPoint(glm::vec2(endX, endY)) {};

	/**
	 Build a Bezier curve

	 @param startPoint Postion of the starting point
	 @param startHandle Postion of the starting point handle
	 @param endHandle Postion of the ending point handle
	 @param endPoint Postion of the ending
	 */
	Bezier(const glm::vec2 &startPoint, const glm::vec2 &startHandle,
		   const glm::vec2 &endHandle, const glm::vec2 &endPoint):
	m_startPoint(startPoint),
	m_startHandle(startHandle),
	m_endHandle(endHandle),
	m_endPoint(endPoint) {};

	/**
	 Return *pointCount* points composing the curve

	 @param pointCount In how many points the curve must be decomposed;
	 @return A vector containing the points
	 */
	std::vector<glm::vec2> getPoints(const uint &pointCount) const;

	glm::vec2 getPoint(const float &percentage) const;

	double getLength();

private:
	glm::vec2 m_startPoint;
	glm::vec2 m_startHandle;
	glm::vec2 m_endHandle;
	glm::vec2 m_endPoint;

	/**
	 Return the nth point on the curve.

	 - values: 0 = starting point, 1 = end point

	 @param A The starting point coordinated
	 @param B The end point coordinates
	 @param coef Point to return in percentage
	 @return The coordinates of the point
	 */
	glm::vec2 getIPointBetween(glm::vec2 A, glm::vec2 B, float coef) const;
};

#endif /* Bezier_hpp */
