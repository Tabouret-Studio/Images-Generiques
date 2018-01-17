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

#include "Bezier.hpp"

class Shape
{
public:
	Shape();

	Shape(const std::vector<Bezier> &paths):
	m_paths(paths) {};

	Shape(const float &width, const float &height, const float &posX, const float &posY):
		m_size(glm::vec2(width, height)),
		m_position(glm::vec2(posX, posY)) {};

	Shape(const std::vector<Bezier> &paths, const float &width, const float &height, const float &posX, const float &posY):
		m_size(glm::vec2(width, height)),
		m_position(glm::vec2(posX, posY)),
		m_paths(paths) {};

	/**
	 Return all the paths in the shape

	 @return Vector of bezier paths
	 */
	inline std::vector<Bezier> getPaths() const { return m_paths; };

	/**
	 Return all the points in the shape

	 @return Vector of 2D points
	 */
	inline std::vector<glm::vec2> getPoints() const { return getPoints(0); };

	/**
	 Return all the points in the shape
	 with n points per path

	 @return Vector of 2D points
	 */
	std::vector<glm::vec2> getPoints(const uint &precision) const;

	/**
	 Return the shape as a Mesh

	 @return A Mesh
	 */
	Mesh * getMesh() const;

private:

	//Dimensions
	glm::vec2 m_size;
	glm::vec2 m_position;

	std::vector<Bezier> m_paths;
};

#endif /* Shape_hpp */
