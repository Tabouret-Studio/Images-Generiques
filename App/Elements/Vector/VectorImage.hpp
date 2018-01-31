//
//  VectorImage.hpp
//  Xcode
//
//  Created by Valentin Dufois on 14/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef VectorImage_hpp
#define VectorImage_hpp

//////////////////////
//Forward declarations
class Mesh;

#include "libraries.hpp"

#include "../Asset.hpp"
#include "Elements/Vector/Bezier.hpp"
#include "Elements/Vector/Shape.hpp"

#include "Utils/DrawCursor.hpp"

#include <iostream>
#include <vector>

class VectorImage : public Asset
{
public:

	//Constructors
	VectorImage();
	VectorImage(const Shape &shape);
	VectorImage(const std::vector<Shape> &shapes);
	VectorImage(const float &width, const float &height);
	VectorImage(const float &width, const float &height, const Shape &shape);
	VectorImage(const float &width, const float &height, const std::vector<Shape> &shapes);
	VectorImage(const VectorImage * vectorImage); //Copy constructor
	

	/**
	 Return all shapes in the image

	 @return shapes vector
	 */
	inline std::vector<Shape> getShapes() const { return m_shapes; };

	/**
	 Return all the Beziers in the image

	 @return Beziers vector
	 */
	std::vector<Bezier> getBeziers() const;

	/**
	 Return all the points in the image
	 Default precision : 150

	 @return All the points in the image
	 */
	inline std::vector<glm::vec3> getPoints() const { return getPoints(1); };

	/**
	 Return all the points in the image for the given precision

	 @return All the points in the image
	 */
	std::vector<glm::vec3> getPoints(const float &precision) const;

	/**
	 Return a Mesh object build with the current image
	 All points are set with 0 Z coordinate
	 Default precision : 150;

	 @return The VectorImage as a renderable Mesh
	 */
	inline Mesh * getMesh() const { return getMesh(1.0); };

	/**
	 Return a Mesh object build with the current image for the given precision
	 All points are set with 0 Z coordinate

	 @return The VectorImage as a renderable Mesh
	 */
	Mesh * getMesh(const float &precision) const;

	/**
	 Get vectorImage cursor

	 @return The cursor
	 */
	inline DrawCursor * getCursor() { return &m_cursor; };

	/**
	 Apply the cursor
	 */
	void applyCursor();

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

	/**
	 Insert shape in the VectorImage

	 @param shape Shape to add
	 */
	VectorImage &operator <<(const Shape &shape);

private:

	std::vector<Shape> m_shapes;

	DrawCursor m_cursor;

	glm::vec3 m_boundsMin;
	glm::vec3 m_boundsMax;

	void calculateBounds();
	void updateBounds(const std::vector<Shape> &shapes);
	void compareAndUpdateBounds(const Shape &shape);
};

#endif /* VectorImage_hpp */
