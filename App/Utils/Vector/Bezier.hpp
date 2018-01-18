//
//  Bezier.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 11/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Bezier_hpp
#define Bezier_hpp

//////////////////////
//Forward declarations
class Mesh;

#include "libraries.hpp"

#include "Utils/DrawCursor.hpp"

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

	Bezier() {};

	/**
	 Set the path dimensions
	 Dimensions are automatically calculated on import

	 @param width Width of the curve
	 @param height Height of the curve
	 */
	void setDimensions(const float &width, const float &height);

	/////////
	//Getters
	inline glm::vec2 getStartPoint() const { return m_startPoint; };
	inline glm::vec2 getStartHandle() const { return m_startHandle; };
	inline glm::vec2 getEndPoint() const { return m_endPoint; };
	inline glm::vec2 getEndHandle() const { return m_endHandle; };

	/**
	 Interpolate the curve and return it composed of number of points based on its length
	 Preferred for easy rendering without any fuss

	 @return A vector containing the points
	 */
	inline std::vector<glm::vec2> getPoints() const { return getPoints(1); };

	/**
	 Interpolate the curve and return it composed of *pointCount* points

	 @param precision In how many points the curve must be decomposed;
	 @return A vector containing the points
	 */
	std::vector<glm::vec2> getPoints(const float &precision) const;

	/**
	 Return a specific point on the curve

	 @param percentage The percentage location of the point (middle point : .5)
	 @return The coordinates of the point
	 */
	glm::vec2 getPoint(const float &percentage) const;

	/**
	 Calculate the approximate length of the curve

	 @return The curve's length in px
	 */
	float getLength() const;

	/**
	 Generate a mesh with the interpolated curve

	 @return A Mesh Object
	 */
	Mesh * getMesh() const;

	/**
	 Return the dimensions of the bezier if defined with setBounds();

	 @return Width and height
	 */
	inline glm::vec2 getDimensions() const { return m_dimensions; };

	/////////////////
	//Transformations

	/**
	 Return the transformation cursor of this mesh

	 @return The mesh's cursor
	 */
	inline DrawCursor * getCursor()  { return &m_cursor; };

	/**
	 Apply the current cursor to the curve coordinates
	 then reset the cursor
	 */
	inline void applyCursor()
	{
		applyCursor(&m_cursor);
		m_cursor.setMatrix(glm::mat4(1.0));
	};

	/**
	 Apply the given cursor to the curve coordinates
	 */
	void applyCursor(const DrawCursor * cursor);

private:
	glm::vec2 m_startPoint;
	glm::vec2 m_startHandle;
	glm::vec2 m_endHandle;
	glm::vec2 m_endPoint;

	glm::vec2 m_dimensions;

	/**
	 Return the nth point on the curve.

	 - values: 0 = starting point, 1 = end point

	 @param A The starting point coordinated
	 @param B The end point coordinates
	 @param coef Point to return in percentage
	 @return The coordinates of the point
	 */
	glm::vec2 getIPointBetween(glm::vec2 A, glm::vec2 B, float coef) const;

	DrawCursor m_cursor;
};

#endif /* Bezier_hpp */
