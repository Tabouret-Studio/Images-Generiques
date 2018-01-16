//
//  Val01.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Val01.hpp"

#include "Utils/Vector/Bezier.hpp"
#include "Utils/Vertex.hpp"

#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"
#include "Engines/RessourcesEngine/Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
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
		VectorImage * svg = *App->ressourcesEngine->getAsset(svgID);

		m_mesh = new Mesh();

		std::vector<glm::vec2> points = svg->getPoints(10);

		for(glm::vec2 point : points)
			*m_mesh << App->ressourcesEngine->gen2DTile(point.x, point.y, rand()%10, rand()%10);

		m_mesh->generate();
		//m_mesh->setRenderFormat(GL_POINTS);

		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void Val01::execute()
	{
		App->renderEngine->setProjection2D();
	}


	//////////////
	// This is executed every frame at render
	///////////
	void Val01::render()
	{
		App->renderEngine->render(m_mesh, m_mesh->getCursor());
	}
}
