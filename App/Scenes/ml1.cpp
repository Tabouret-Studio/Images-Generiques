//
//  ml1.cpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 10/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "ml1.hpp"

#include "Elements/Vector/Bezier.hpp"
#include "Utils/Vertex.hpp"

#include "Elements/Vector/VectorImage.hpp"
#include "Elements/Mesh.hpp"
#include "Elements/jsonObject.hpp"
#include "Elements/Asset.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/IndexEngine/IndexEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"
#include "Utils/Selector/Item.hpp"
#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"
#include "Engines/RessourcesEngine/Importers/jsonImporter.hpp"

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
		rId svgID = App->ressourcesEngine->loadAsset("ml.svg", VECTOR);
		VectorImage * svg = *App->ressourcesEngine->getAsset(svgID);

		jsonImporter jImport;
		rId jsonId = App->ressourcesEngine->loadAsset("indexExample.json", JSON);
		jsonObject * jsonFile = *App->ressourcesEngine->getAsset(jsonId);

		 m_mesh = svg->getMesh();

		 m_mesh->generate();
		 m_mesh->getCursor()->translate(App->getWidth()/2, App->getHeight()/2, 0); 
 
	 	

		//App->indexEngine->setImagesIdsPaths(jsonFile);


	    App->renderEngine->setProjection2D(); 
	    SVGExporter fExport;
	    fExport.exportSVG(svg, "ml2");

	    


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
		float scrollAmount = App->appEngine->getMouse().scrollY/10.0f;
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
