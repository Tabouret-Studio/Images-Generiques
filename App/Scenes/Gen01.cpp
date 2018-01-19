//
//  Gen01.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Gen01.hpp"

#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"
#include "Engines/RessourcesEngine/Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

namespace Scenes
{
	void Gen01::load()
	{
		Scene * scene = new Gen01();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void Gen01::init()
	{
		//Load SVG
		rId svgID = App->ressourcesEngine->loadAsset("handComputer.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);

		m_mesh = m_svg->getMesh();
		m_mesh->generate();
		m_mesh->getCursor()
			->translate(App->getWidth()/2, App->getHeight()/2, 0);

		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void Gen01::execute()
	{
		float scrollAmount = App->appEngine->getMouse().scrollY/10.0f;
		m_mesh->getCursor()->scale(1+scrollAmount, 1+scrollAmount, 1);

	}


	//////////////
	// This is executed every frame at render
	///////////
	void Gen01::render()
	{
		App->renderEngine->setProjection2D();
		m_mesh->render();
	}
}
