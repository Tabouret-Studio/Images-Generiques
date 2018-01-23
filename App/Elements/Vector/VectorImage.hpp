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

#include "Asset.hpp"
#include "Elements/Vector/Bezier.hpp"
#include "Elements/Vector/Shape.hpp"

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


	/**
	 Set the picture dimensions

	 @param width New width
	 @param height New height
	 */
	void setDimensions(const float &width, const float &height);

	/**
	 Return the with of the image

	 @return Width
	 */
	inline uint getWidth() const { return m_width; }

	/**
	 Return the height of the image

	 @return Height
	 */
	inline uint getHeight() const { return m_height; }

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
	inline Mesh * getMesh() const { return getMesh(0); };

	/**
	 Return a Mesh object build with the current image for the given precision
	 All points are set with 0 Z coordinate

	 @return The VectorImage as a renderable Mesh
	 */
	Mesh * getMesh(const uint &precision) const;

	inline VectorImage &operator <<(const Shape &shape) { m_shapes.push_back(shape); return *this; }

private:

	float m_width;
	float m_height;

	std::vector<Shape> m_shapes;
};

#endif /* VectorImage_hpp */
