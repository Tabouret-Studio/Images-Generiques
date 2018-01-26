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

/**
 Allow for easy manipulation of bezier curves.
 A bezier curve is composed of 4 points and defines a curve.
 */
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
	 @param endY Y position of the ending point
	 */
	Bezier(const float &startX, const float &startY,
		   const float &startHX, const float &startHY,
		   const float &endHX, const float &endHY,
		   const float &endX, const float &endY):
	m_startPoint(glm::vec3(startX, startY, 0)),
	m_startHandle(glm::vec3(startHX, startHY, 0)),
	m_endHandle(glm::vec3(endHX, endHY, 0)),
	m_endPoint(glm::vec3(endX, endY, 0)) {
		calculateBounds();
	};

	/**
	 Build a Bezier curve

	 @param startX X position of the starting point
	 @param startY Y position of the starting point
	 @param startZ Z position of the starting point
	 @param startHX X position of the starting point handle
	 @param startHY Y position of the starting point handle
	 @param startHZ Z position of the starting point handle
	 @param endHX X position of the ending point handle
	 @param endHY Y position of the ending point handle
	 @param endHZ Z position of the ending point handle
	 @param endX X position of the ending point
	 @param endY Y position of the ending point
	 @param endZ Z position of the ending point
	 */
	Bezier(const float &startX, const float &startY, const float &startZ,
		   const float &startHX, const float &startHY, const float &startHZ,
		   const float &endHX, const float &endHY, const float &endHZ,
		   const float &endX, const float &endY, const float &endZ):
	m_startPoint(glm::vec3(startX, startY, startZ)),
	m_startHandle(glm::vec3(startHX, startHY, startHZ)),
	m_endHandle(glm::vec3(endHX, endHY, endHZ)),
	m_endPoint(glm::vec3(endX, endY, endZ)) {
		calculateBounds();
	};

	/**
	 Build a Bezier curve

	 @param startPoint Postion of the starting point
	 @param startHandle Postion of the starting point handle
	 @param endHandle Postion of the ending point handle
	 @param endPoint Postion of the ending
	 */
	Bezier(const glm::vec2 &startPoint, const glm::vec2 &startHandle,
		   const glm::vec2 &endHandle, const glm::vec2 &endPoint):
	m_startPoint(glm::vec3(startPoint, 0)),
	m_startHandle(glm::vec3(startHandle, 0)),
	m_endHandle(glm::vec3(endHandle, 0)),
	m_endPoint(glm::vec3(endPoint, 0)) {
		calculateBounds();
	};

	/**
	 Build a Bezier curve

	 @param startPoint Postion of the starting point
	 @param startHandle Postion of the starting point handle
	 @param endHandle Postion of the ending point handle
	 @param endPoint Postion of the ending
	 */
	Bezier(const glm::vec3 &startPoint, const glm::vec3 &startHandle,
		   const glm::vec3 &endHandle, const glm::vec3 &endPoint):
	m_startPoint(startPoint),
	m_startHandle(startHandle),
	m_endHandle(endHandle),
	m_endPoint(endPoint) {
		calculateBounds();
	};

	Bezier():m_dimensions(glm::vec3(0)) {};

	/**
	 Set the path dimensions
	 Dimensions are automatically calculated on import

	 @param width Width of the curve
	 @param height Height of the curve
	 */
	void setDimensions(const float &width, const float &height, const float &depth);

	/////////
	//Getters
	inline glm::vec3 getStartPoint() const { return m_startPoint; };
	inline glm::vec3 getStartHandle() const { return m_startHandle; };
	inline glm::vec3 getEndPoint() const { return m_endPoint; };
	inline glm::vec3 getEndHandle() const { return m_endHandle; };

	/**
	 Interpolate the curve and return it composed of number of points based on its length
	 Preferred for easy rendering without any fuss

	 @return A vector containing the points
	 */
	inline std::vector<glm::vec3> getPoints() const { return getPoints(1); };

	/**
	 Interpolate the curve and return it composed of *pointCount* points

	 @param precision In how many points the curve must be decomposed;
	 @return A vector containing the points
	 */
	std::vector<glm::vec3> getPoints(const float &precision) const;

	/**
	 Return a specific point on the curve

	 @param percentage The percentage location of the point (middle point : .5)
	 @return The coordinates of the point
	 */
	glm::vec3 getPoint(const float &percentage) const;

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
	 Return the dimensions

	 @return Width and height
	 */
	inline glm::vec3 getDimensions() const { return m_dimensions; };

	/**
	 Return the position of the bezier (min XYZ coordinates)

	 @return Width and height
	 */
	inline glm::vec3 getPosition() const { return m_position; };

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

	/**
	 Move the bezier startPoint to the given position

	 @param dest Desitination point
	 */
	void move(const glm::vec3 &dest);

private:
	glm::vec3 m_startPoint;
	glm::vec3 m_startHandle;
	glm::vec3 m_endHandle;
	glm::vec3 m_endPoint;

	glm::vec3 m_dimensions;
	glm::vec3 m_position;

	/**
	 Return the nth point on the curve.

	 - values: 0 = starting point, 1 = end point

	 @param A The starting point coordinated
	 @param B The end point coordinates
	 @param coef Point to return in percentage
	 @return The coordinates of the point
	 */
	glm::vec3 getIPointBetween(glm::vec3 A, glm::vec3 B, float coef) const;

	/**
	 Calculate the mesh boundaries
	 */
	void calculateBounds();

	DrawCursor m_cursor;
};

#endif /* Bezier_hpp */
