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
		if(m_meshs.size() == 0)
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

		for(Mesh * mesh : m_meshs)
		{
			glm::vec3 meshDims = mesh->getDimensions();
			glm::vec3 meshPos = mesh->getBoundariesMin();

			//Move bezier to origin
			float scale = std::min(workingDimensions.x / meshDims.x, workingDimensions.y / meshDims.y) * 0.9f;

			mesh->getCursor()->reset()
				->translate(-(meshPos.x + meshDims.x / 2.0), -(meshPos.y + meshDims.y / 2.0), 0)
				->translate(glm::vec3(renderCenter, 0))
				->scale(scale, scale, 0);

			App->renderEngine->setProjection2D();
			mesh->render();
		}
	}

	void SimpleRenderer::setBounds(const uint &marginLeft, const uint &marginTop, const uint &width, const uint &height)
	{
		m_renderMargin = glm::vec2(marginLeft, marginTop);
		m_renderDimensions = glm::vec2(width, height);
	}

	void SimpleRenderer::clear()
	{
		m_meshs.clear();
	}

	void SimpleRenderer::addMesh(Mesh * mesh)
	{
		if(mesh == nullptr)
			return;

		if(!mesh->isGenerated())
			mesh->generate();

		m_meshs.push_back(mesh);
	}
}
