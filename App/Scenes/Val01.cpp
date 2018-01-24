//
//  Val01.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Val01.hpp"

#include "Elements/Vector/Bezier.hpp"

#include "Elements/Vector/VectorImage.hpp"
#include "Elements/Font.hpp"
#include "Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Utils/Selector/Item.hpp"

namespace Scenes
{
	void Val01::load()
	{
		Scene * scene = new Val01();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void Val01::init()
	{
		//Load SVG
		//Utils::NSVG svg = Utils::NSVG("Assets/SVG/ml.svg");
		rId svgID = App->ressourcesEngine->loadAsset("artist.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);

		m_mesh = m_svg->getMesh();
		m_mesh->generate();
//		m_mesh->getCursor()
//		->translate(App->getWidth()/2, App->getHeight()/2, 0);

		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void Val01::execute()
	{
	}


	//////////////
	// This is executed every frame at render
	///////////
	void Val01::render()
	{
		App->renderEngine->setProjection2D();

		App->renderEngine->render(m_mesh, m_mesh->getCursor());
	}
}
