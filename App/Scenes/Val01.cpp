//
//  Val01.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Val01.hpp"

#include "Utils/Vector/Bezier.hpp"

#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"
#include "Engines/RessourcesEngine/Elements/Font.hpp"
#include "Engines/RessourcesEngine/Elements/Mesh.hpp"
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
		rId svgID = App->ressourcesEngine->loadAsset("github.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);

		std::vector<glm::vec2> points = m_svg->getPoints(.05);

		m_mesh = new Mesh();

		for(glm::vec2 point : points)
			*m_mesh << App->ressourcesEngine->gen2DTile(point.x, point.y, rand()%20, rand()%20);

		m_mesh->generate();
		m_mesh->getCursor()
			->translate(App->getWidth()/2, App->getHeight()/2, 0)
			->scale(.5, .5, .5);

		App->renderEngine->setProjection2D();

		//std::cout << "Val 01 init" << std::endl;
	}


	//////////////
	// This is executed every frame before render
	///////////
	void Val01::execute()
	{
		//std::cout << "Val 01 executed" << std::endl;
	}


	//////////////
	// This is executed every frame at render
	///////////
	void Val01::render()
	{
		App->renderEngine->setProjection2D();

		App->renderEngine->render(m_mesh, m_mesh->getCursor());

		//std::cout << "Val 01 rendered" << std::endl;
	}
}
