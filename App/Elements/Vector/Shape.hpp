//
//  Shape.hpp
//  Xcode
//
//  Created by Valentin Dufois on 16/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

//////////////////////
//Forward declarations
class Mesh;

#include "libraries.hpp"

#include "Utils/DrawCursor.hpp"
#include "Bezier.hpp"

/**
 Allow for easy manipulation of 2D shapes composed of bezier curves.
 */
class Shape
{
public:
	Shape() {};

	Shape(const Bezier &path):
		m_paths({path}),
		m_boundsMin(path.getPosition()),
		m_boundsMax(path.getBoundsMax()) {};

	Shape(const std::vector<Bezier> &paths):
		m_paths(paths) { calculateBounds(); };

	/**
	 Return all the paths in the shape

	 @return Vector of bezier paths
	 */
	inline std::vector<Bezier> * getPaths() { return &m_paths; };

	/**
	 Return all the points in the shape

	 @return Vector of 2D points
	 */
	inline std::vector<glm::vec3> getPoints() const { return getPoints(1); };

	/**
	 Return all the points in the shape
	 with n points per path

	 @return Vector of 2D points
	 */
	std::vector<glm::vec3> getPoints(const float &precision) const;

	inline Mesh * getMesh() const { return getMesh(1); };

	/**
	 Return the shape as a Mesh

	 @return A Mesh
	 */
	Mesh * getMesh(const float &precision) const;

	/**
	 Tell shape position (min XYZ coordinates)

	 @return The position
	 */
	inline glm::vec3 getPosition() const { return m_boundsMin; };

	/**
	 Tell the dimensions of the shape

	 @return XYZ dimensions
	 */
	inline glm::vec3 getDimensions() const { return glm::abs(m_boundsMax - m_boundsMin); };

	/**
	 Tell the shape max XYZ coordinates

	 @return XYZ coordinates
	 */
	inline glm::vec3 getBoundsMax() const { return m_boundsMax; };

	///////////
	//Insertion

	Shape &operator << (const Bezier &path);

	/////////////////
	//Transformations

	inline DrawCursor * getCursor() { return &m_cursor; };

	inline void applyCursor() { applyCursor(glm::mat4(1.0)); };

	void applyCursor(const glm::mat4 &imageCursor);

private:

	std::vector<Bezier> m_paths;

	glm::vec3 m_boundsMin;
	glm::vec3 m_boundsMax;

	DrawCursor m_cursor;

	void calculateBounds();
	void updateBounds(const std::vector<Bezier> &paths);

	void compareAndUpdateBounds(const Bezier &path);

	
};

#endif /* Shape_hpp */
