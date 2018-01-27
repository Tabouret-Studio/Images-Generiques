//
//  VectorImage.cpp
//  Xcode
//
//  Created by Valentin Dufois on 14/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "VectorImage.hpp"

#include "../Mesh.hpp"

VectorImage::VectorImage():
	Asset(VECTOR),
	m_width(500),
	m_height(500) {}

VectorImage::VectorImage(const Shape &shape):
	Asset(VECTOR),
	m_width(500),
	m_height(500),
	m_shapes({shape}) {}

VectorImage::VectorImage(const std::vector<Shape> &shapes):
	Asset(VECTOR),
	m_width(500),
	m_height(500),
	m_shapes(shapes) {}

VectorImage::VectorImage(const float &width, const float &height):
	Asset(VECTOR),
	m_width(width),
	m_height(height) {}

VectorImage::VectorImage(const float &width, const float &height, const Shape &shape):
	Asset(VECTOR),
	m_width(width),
	m_height(height),
	m_shapes({shape}) {}

VectorImage::VectorImage(const float &width, const float &height, const std::vector<Shape> &shapes):
	Asset(VECTOR),
	m_width(width),
	m_height(height),
	m_shapes(shapes) {}



void VectorImage::setDimensions(const float &width, const float &height)
{
	m_width = width;
	m_height = height;
}

std::vector<Bezier> VectorImage::getBeziers() const
{

	std::vector<Bezier> curves;
	std::vector<Bezier> paths;

	// Parse SVG
	for(Shape shape : m_shapes) {
		paths = shape.getPaths();
		curves.insert(curves.end(), paths.begin(), paths.end());
	}

	return curves;
}


std::vector<glm::vec3> VectorImage::getPoints(const float &precision) const
{
	std::vector<glm::vec3> vertices, pathVertices;

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
	Mesh * shapeMesh;

	// Parse SVG
	for(std::vector<Shape>::const_iterator shape = m_shapes.begin(); shape != m_shapes.end(); ++shape)
	{
		shapeMesh = shape->getMesh(precision);
		*mesh << shapeMesh;
		delete shapeMesh;
	}

	mesh->setRenderFormat(GL_POINTS);
	mesh->getCursor()->setMatrix(m_cursor);
	mesh->applyCursor();

	return mesh;
}

void VectorImage::applyCursor()
{
	for(std::vector<Shape>::iterator shape = m_shapes.begin(); shape != m_shapes.end(); ++shape)
	{
		shape->getCursor()->setMatrix(m_cursor * shape->getCursor()->getMatrix());
		shape->applyCursor();
	}

	m_cursor.reset();

	calculateBounds();
}

VectorImage &VectorImage::operator <<(const Shape &shape)
{
	m_shapes.push_back(shape);
	updateBounds({shape});

	return *this;
}

void VectorImage::calculateBounds()
{
	if(m_shapes.size() == 0)
		return;

	m_boundsMin = m_shapes[0].getPosition();
	m_boundsMax = m_shapes[0].getBoundsMax();

	for(std::vector<Shape>::const_iterator it = m_shapes.begin() + 1; it != m_shapes.end(); ++it)
		compareAndUpdateBounds(*it);
}

void VectorImage::updateBounds(const std::vector<Shape> &shapes)
{
	if(m_shapes.size() == 1)
	{
		m_boundsMin = m_shapes[0].getPosition();
		m_boundsMax = m_shapes[0].getBoundsMax();

		return;
	}

	for(std::vector<Shape>::const_iterator it = shapes.begin() + 1; it != shapes.end(); ++it)
		compareAndUpdateBounds(*it);
}

void VectorImage::compareAndUpdateBounds(const Shape &shape)
{
	//Min
	if(shape.getPosition().x < m_boundsMin.x) m_boundsMax.x = shape.getPosition().x;
	if(shape.getPosition().y < m_boundsMin.y) m_boundsMax.y = shape.getPosition().y;
	if(shape.getPosition().z < m_boundsMin.z) m_boundsMax.z = shape.getPosition().z;

	//Max
	if(shape.getBoundsMax().x > m_boundsMax.x) m_boundsMax.x = shape.getBoundsMax().x;
	if(shape.getBoundsMax().y > m_boundsMax.y) m_boundsMax.y = shape.getBoundsMax().y;
	if(shape.getBoundsMax().z > m_boundsMax.z) m_boundsMax.z = shape.getBoundsMax().z;
}
