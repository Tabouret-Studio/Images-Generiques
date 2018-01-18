//
//  MeshGroup.cpp
//  Xcode
//
//  Created by Valentin Dufois on 18/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "MeshGroup.hpp"
#include "Engines/RessourcesEngine/Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Core/AppObject.hpp"

void MeshGroup::render()
{
	DrawCursor cursor;

	for(std::vector<Mesh *>::const_iterator it = m_meshs.begin(); it != m_meshs.end(); ++it)
	{
		cursor = m_cursor * *(*it)->getCursor();
		App->renderEngine->render((*it), &cursor);
	}
}

MeshGroup &MeshGroup::operator<<(Mesh * mesh)
{
	m_meshs.push_back(mesh);
	return *this;
}

MeshGroup &MeshGroup::operator<<(std::vector<Mesh *> meshs)
{
	m_meshs.insert(m_meshs.end(), meshs.begin(), meshs.end());
	return *this;
}

MeshGroup::~MeshGroup()
{

	for(std::vector<Mesh *>::const_iterator it = m_meshs.begin(); it != m_meshs.end(); ++it)
	{
		delete (*it);
	}
}
