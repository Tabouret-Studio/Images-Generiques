//
//  SimpleRenderer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 29/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "SimpleRenderer.hpp"

#include "Core/AppObject.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"

#include "Elements/Mesh.hpp"

namespace Scenes
{
	void SimpleRenderer::load()
	{
		Scene * scene = new SimpleRenderer();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void SimpleRenderer::init()
	{
	}


	//////////////
	// This is executed every frame before render
	///////////
	void SimpleRenderer::execute()
	{
	}


	//////////////
	// This is executed every frame at render
	///////////
	void SimpleRenderer::render()
	{
		if(m_mesh == nullptr)
			return;

		glm::vec2 renderCenter(m_renderMargin);
		glm::vec2 workingDimensions;

		//Calculate working dimensions
		if(m_renderDimensions.x == 0)
			workingDimensions.x = App->getWidth() - m_renderMargin.x;
		else
			workingDimensions.x = m_renderDimensions.x;

		if(m_renderDimensions.y == 0)
			workingDimensions.y = App->getHeight() - m_renderMargin.y;
		else
			workingDimensions.y = m_renderDimensions.y;

		renderCenter += workingDimensions / 2.0;

		glm::vec3 meshDims = m_mesh->getDimensions();

		float scale = std::min(workingDimensions.x / meshDims.x, workingDimensions.y / meshDims.y) * 0.9f;

		m_mesh->getCursor()->reset()->translate(glm::vec3(renderCenter, 0))->scale(scale, scale, 0);

		App->renderEngine->setProjection2D();
		m_mesh->render();
	}

	void SimpleRenderer::setBounds(const uint &marginLeft, const uint &marginTop, const uint &width, const uint &height)
	{
		m_renderMargin = glm::vec2(marginLeft, marginTop);
		m_renderDimensions = glm::vec2(width, height);
	}

	void SimpleRenderer::setMesh(Mesh * mesh)
	{
		m_mesh = mesh;

		if(m_mesh == nullptr)
			return;

		if(!m_mesh->isGenerated())
			m_mesh->generate();
	}
}
