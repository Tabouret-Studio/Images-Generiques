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

Mesh * Shape::getMesh(const float &precision) const
{
	Mesh * mesh = new Mesh();
	Mesh * bezMesh;

	for(std::vector<Bezier>::const_iterator it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		bezMesh = (*it).getMesh(precision);
		*mesh << bezMesh;
		delete bezMesh;
	}

	mesh->getCursor()->setMatrix(m_cursor);
	mesh->applyCursor();

	return mesh;
}

void Shape::applyCursor(const glm::mat4 &imageCursor)
{
	DrawCursor transformedCursor = imageCursor * m_cursor.getMatrix();

	for(std::vector<Bezier>::iterator bezier = m_paths.begin(); bezier != m_paths.end(); ++bezier)
	{
		bezier->applyCursor(transformedCursor.getMatrix());
	}

	calculateBounds();
	m_cursor.reset();
}

Shape &Shape::operator<<(const Bezier &path)
{
	m_paths.push_back(path);
	updateBounds({path});

	return *this;
}

void Shape::calculateBounds()
{
	if(m_paths.size() == 0)
		return;

	m_boundsMin = m_paths[0].getPosition();
	m_boundsMax = m_paths[0].getBoundsMax();

	for(std::vector<Bezier>::const_iterator it = m_paths.begin() + 1; it != m_paths.end(); ++it)
		compareAndUpdateBounds(*it);
}

void Shape::updateBounds(const std::vector<Bezier> &paths)
{
	if(m_paths.size() == 1)
	{
		m_boundsMin = m_paths[0].getPosition();
		m_boundsMax = m_paths[0].getBoundsMax();

		return;
	}

	for(std::vector<Bezier>::const_iterator it = paths.begin() + 1; it != paths.end(); ++it)
		compareAndUpdateBounds(*it);
}

void Shape::compareAndUpdateBounds(const Bezier &path)
{
	//Min
	if(path.getPosition().x < m_boundsMin.x) m_boundsMin.x = path.getPosition().x;
	if(path.getPosition().y < m_boundsMin.y) m_boundsMin.y = path.getPosition().y;
	if(path.getPosition().z < m_boundsMin.z) m_boundsMin.z = path.getPosition().z;

	//Max
	if(path.getBoundsMax().x > m_boundsMax.x) m_boundsMax.x = path.getBoundsMax().x;
	if(path.getBoundsMax().y > m_boundsMax.y) m_boundsMax.y = path.getBoundsMax().y;
	if(path.getBoundsMax().z > m_boundsMax.z) m_boundsMax.z = path.getBoundsMax().z;
}
