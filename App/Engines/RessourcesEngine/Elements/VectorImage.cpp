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

VectorImage::VectorImage(const std::vector<Bezier> &paths):
	Asset(VECTOR),
	m_width(500),
	m_height(500),
	m_paths(paths) {};

VectorImage::VectorImage(const float &width, const float &height):
	Asset(VECTOR),
	m_width(width),
	m_height(height) {};

VectorImage::VectorImage(const float &width, const float &height, const std::vector<Bezier> &paths):
	Asset(VECTOR),
	m_width(width),
	m_height(height),
	m_paths(paths) {};

void VectorImage::setDimensions(const float &width, const float &height)
{
	m_width = width;
	m_height = height;
}

std::vector<glm::vec2> VectorImage::getPoints(const uint &precision) const
{
	std::vector<glm::vec2> vertices, pathVertices;

	// Parse SVG
	for(std::vector<Bezier>::const_iterator it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		pathVertices = (*it).getPoints(0);

		vertices.insert(vertices.end(), pathVertices.begin(), pathVertices.end());
	}

	return vertices;
}

Mesh * VectorImage::getMesh(const uint &precision) const
{
	std::vector<glm::vec2> vertices2D = getPoints(precision);
	std::vector<Vertex> vertices3D;

	// Parse SVG
	for(std::vector<glm::vec2>::const_iterator it = vertices2D.begin(); it != vertices2D.end(); ++it)
	{
		vertices3D.push_back(Vertex(glm::vec3(*it, 0)));
	}

	Mesh * mesh = new Mesh(vertices3D);
	mesh->setRenderFormat(GL_POINTS);

	return mesh;
}
