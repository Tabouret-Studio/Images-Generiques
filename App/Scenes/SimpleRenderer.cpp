//
//  simpleRenderer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 29/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "simpleRenderer.hpp"

namespace Scenes
{
	void simpleRenderer::load()
	{
		Scene * scene = new simpleRenderer();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void simpleRenderer::init()
	{
	}


	//////////////
	// This is executed every frame before render
	///////////
	void simpleRenderer::execute()
	{
	}


	//////////////
	// This is executed every frame at render
	///////////
	void simpleRenderer::render()
	{
	}

	void simpleRenderer::setBounds(const uint &marginLeft, const uint &marginTop, const uint &width, const uint &height)
	{
		m_renderMargin = glm::vec2(marginLeft, marginTop);
		m_renderDimensions = glm::vec2(width, height);
	}
}
