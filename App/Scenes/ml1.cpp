//
//  ml1.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "ml1.hpp"

#include "Utils/Vector/Bezier.hpp"
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

		//m_mesh = svg->getMesh();

		 m_mesh = new Mesh(); 
 
	    std::vector<glm::vec2> points = svg->getPoints(10); 
	 
	    for(glm::vec2 point : points) 
	      *m_mesh << App->ressourcesEngine->gen2DTile(point.x, point.y, 10, 10); 
	 
	    m_mesh->generate(); 
	    //m_mesh->setRenderFormat(GL_POINTS); 
	    //m_mesh->setRenderFormat(GL_POINTS); 
	 
	    App->renderEngine->setProjection2D(); 

		/*m_mesh = new Mesh();
		Mesh * mesh_ptr;

		std::vector<glm::vec2> points = svg->getPoints();
		for(std::vector<glm::vec2>::iterator it = points.begin();
			it != points.end(); ++it)
		{
			mesh_ptr = App->ressourcesEngine->gen2DTile((*it).x, (*it).y, 5, 5);
			mesh_ptr->applyCursor();
			m_mesh->appendVertex(mesh_ptr->getVertexList());
		}

		std::cout << "mdr " << glm::to_string(m_mesh->getVertexList()[0].position) << std::endl;
		m_mesh->generate();
		m_mesh->setRenderFormat(GL_POINTS);

		App->renderEngine->setProjection2D();*/
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
