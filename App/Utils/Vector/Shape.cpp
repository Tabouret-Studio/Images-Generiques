//
//  Shape.cpp
//  Xcode
//
//  Created by Valentin Dufois on 16/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Shape.hpp"

#include "Engines/RessourcesEngine/Elements/Mesh.hpp"

std::vector<glm::vec2> Shape::getPoints(const float &precision) const
{
	std::vector<glm::vec2> points;
	std::vector<glm::vec2> pathPoints;

	for(std::vector<Bezier>::const_iterator it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		pathPoints = (*it).getPoints(precision);
		points.insert(points.end(), pathPoints.begin(), pathPoints.end());
	}

	return points;
}

Mesh * Shape::getMesh() const
{
	Mesh * mesh = new Mesh();

	for(std::vector<Bezier>::const_iterator it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		*mesh << (*it).getMesh();
	}

	return mesh;
}

void Shape::applyCursor(DrawCursor * cursor)
{
	for(std::vector<Bezier>::iterator it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		(*it).applyCursor(cursor);
	}

	m_size = glm::vec2(cursor->getMatrix() * glm::vec4(m_size, 0, 1));
	m_size = glm::vec2(cursor->getMatrix() * glm::vec4(m_size, 0, 1));
}
