//
//  VectorImage.cpp
//  Xcode
//
//  Created by Valentin Dufois on 14/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "VectorImage.hpp"

#include "Mesh.hpp"

VectorImage::VectorImage():
	Asset(VECTOR),
	m_width(500),
	m_height(500) {};

VectorImage::VectorImage(const std::vector<Shape> &shapes):
	Asset(VECTOR),
	m_width(500),
	m_height(500),
	m_shapes(shapes) {};

VectorImage::VectorImage(const float &width, const float &height):
	Asset(VECTOR),
	m_width(width),
	m_height(height) {};

VectorImage::VectorImage(const float &width, const float &height, const std::vector<Shape> &shapes):
	Asset(VECTOR),
	m_width(width),
	m_height(height),
	m_shapes(shapes) {};

void VectorImage::setDimensions(const float &width, const float &height)
{
	m_width = width;
	m_height = height;
}

std::vector<glm::vec2> VectorImage::getPoints(const float &precision) const
{
	std::vector<glm::vec2> vertices, pathVertices;

	// Parse SVG
	for(std::vector<Shape>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		pathVertices = (*it).getPoints(precision);

		vertices.insert(vertices.end(), pathVertices.begin(), pathVertices.end());
	}

	return vertices;
}

Mesh * VectorImage::getMesh(const uint &precision) const
{
	Mesh * mesh = new Mesh();

	// Parse SVG
	for(std::vector<Shape>::const_iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		*mesh << (*it).getMesh();
	}

	mesh->setRenderFormat(GL_POINTS);

	return mesh;
}