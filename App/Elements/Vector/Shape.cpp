//
//  Shape.cpp
//  Xcode
//
//  Created by Valentin Dufois on 16/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Shape.hpp"

#include "Elements/Mesh.hpp"

std::vector<glm::vec3> Shape::getPoints(const float &precision) const
{
	std::vector<glm::vec3> points;
	std::vector<glm::vec3> pathPoints;

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
	Mesh * bezMesh;

	for(std::vector<Bezier>::const_iterator it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		bezMesh = (*it).getMesh();
		*mesh << bezMesh;
	}

	mesh->getCursor()->setMatrix(m_cursor);
	return mesh;
}

void Shape::applyCursor(DrawCursor * cursor)
{
	for(std::vector<Bezier>::iterator it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		(*it).applyCursor(cursor);
	}
}

Shape &Shape::operator<<(const Bezier &path)
{
	m_paths.push_back(path);
	return *this;
}
