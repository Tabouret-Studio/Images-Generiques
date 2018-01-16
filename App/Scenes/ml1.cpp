//
//  ml1.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "ml1.hpp"

#include "Utils/Bezier.hpp"
#include "Utils/Vertex.hpp"

#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"
#include "Engines/RessourcesEngine/Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Utils/Selector/Item.hpp"

#include <iostream>

namespace Scenes
{
	void ml1::load()
	{
		Scene * scene = new ml1();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void ml1::init()
	{
		//Load SVG
		//Utils::NSVG svg = Utils::NSVG("Assets/SVG/ml.svg");
		rId svgID = App->ressourcesEngine->loadAsset("github.svg", VECTOR);
		VectorImage * svg = *App->ressourcesEngine->getAsset(svgID);

		m_mesh = svg->getMesh();
		m_mesh->generate();
		m_mesh->setRenderFormat(GL_POINTS);

		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void ml1::execute()
	{
		float scrollAmount = App->appEngine->getMouse().scroll/10.0f;
		if(scrollAmount != 0) {
			m_mesh->getCursor()->scale(1+scrollAmount, 1+scrollAmount, 1);
		}
	}


	//////////////
	// This is executed every frame at render
	///////////
	void ml1::render()
	{
		App->renderEngine->render(m_mesh, m_mesh->getCursor());
	}
}
