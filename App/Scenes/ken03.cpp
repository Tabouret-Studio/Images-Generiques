//
//  ken03.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ken03.hpp"

#include "Elements/Vector/VectorImage.hpp"
#include "Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"
#include "Engines/RessourcesEngine/Exporters/VectorImagesToJSONExporter.hpp"
#include "Engines/RessourcesEngine/Importers/JSONToVectorImagesImporter.hpp"

#include "Engines/GeneratorEngine/GeneratorEngine.hpp"
#include "Engines/GeneratorEngine/InstructionsProtocol/InstructionsProtocol.hpp"

namespace Scenes
{
	void ken03::load()
	{
		Scene * scene = new ken03();

		scene->init();


		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void ken03::init()
	{

		// INSTRUCTION A UPGRADE FOR MULTISVG PROCESS
		//Loading
		rId svgID = App->ressourcesEngine->loadAsset("github.svg", VECTOR);
		m_svg.push_back(*App->ressourcesEngine->getAsset(svgID));

		// rId svgID2 = App->ressourcesEngine->loadAsset("handComputer.svg", VECTOR);
		// m_svg.push_back(*App->ressourcesEngine->getAsset(svgID2));


		m_zoomLevel = 1;
		int i=0;
		//Instructions
		InstructionsProtocol protocol({
			//"SHAPE_SYMX"
			//"PATHS_ORDER_RANDOMIZER"
			"SHAPE_SYMY"
		});

		std::vector<VectorImage*> imageTransformed = protocol.execute(m_svg);
		std::cout<<"Taille de m_svg: "<<m_svg.size()<<std::endl;
		std::cout<<"Taille de imageTransformed: "<<imageTransformed.size()<<std::endl;
		//Export
		SVGExporter exporter;
		for (VectorImage* img : imageTransformed)
		{
			std::cout<<"segfault heeeeere"<<std::endl;
			exporter.exportSVG(img, "testInstruction_"+std::to_string(i));
			std::cout<<"segfault heeeeere"<<std::endl;
			m_mesh.push_back(img->getMesh());

			m_mesh[i]->generate();
			m_mesh[i]->setRenderFormat(GL_POINTS);
	
			glPointSize(1);
	
			m_mesh[i]->getCursor()
				->reset()->translate(App->getWidth()/2, App->getHeight()/2, 1)->scale(1, 1, 1);
			std::cout<<"Opération sur svg numéro "<<i<<std::endl;
			i++;
		}
		

		//Generate and display Mesh
		//m_mesh = m_svg->getMesh();

		

		//m_mesh->getCursor()->reset();
		//m_mesh->applyCursor();
		//m_mesh->getCursor()->rotate(180, 1, 0, 0)->translate(0, 0, (m_svg->getHeight() / 2.f))->scale(10, 10, 1);

	}


	//////////////
	// This is executed every frame before render
	///////////
	void ken03::execute()
	{
		m_zoomLevel += App->appEngine->getMouse().scrollY / 50.f;
		if(m_zoomLevel < 0)
			m_zoomLevel = 0;

	}


	//////////////
	// This is executed every frame at render
	///////////
	void ken03::render()
	{
		App->renderEngine->setProjection2D();

		for (Mesh* mesh : m_mesh)
		{
			mesh->getCursor()->reset()
			->translate(App->getWidth()/2, App->getHeight()/2, 1)->scale(m_zoomLevel, m_zoomLevel, 0);

			mesh->render();
		}
		

	}
}
