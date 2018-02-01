//
//  ken01.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ken01.hpp"

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
	void ken01::load()
	{
		Scene * scene = new ken01();

		scene->init();


		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void ken01::init()
	{
		//Loading
		rId svgID = App->ressourcesEngine->loadAsset("github.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);
		m_zoomLevel = 1;
		
		//Instructions
		InstructionsProtocol protocol({
			"PATHS_INDEX"
		});

		VectorImage * imageTransformed = protocol.execute({m_svg})[0];

		//Export
		SVGExporter exporter;
		exporter.exportSVG(imageTransformed, "testInstruction");

		//Generate and display Mesh
		//m_mesh = m_svg->getMesh();

		m_mesh = imageTransformed->getMesh();

		m_mesh->generate();
		m_mesh->setRenderFormat(GL_POINTS);

		glPointSize(1);

		m_mesh->getCursor()
			->reset()->translate(App->getWidth()/2, App->getHeight()/2, 1)->scale(1, 1, 1);

		//m_mesh->getCursor()->reset();
		//m_mesh->applyCursor();
		//m_mesh->getCursor()->rotate(180, 1, 0, 0)->translate(0, 0, (m_svg->getHeight() / 2.f))->scale(10, 10, 1);

	}


	//////////////
	// This is executed every frame before render
	///////////
	void ken01::execute()
	{
		m_zoomLevel += App->appEngine->getMouse().scrollY / 50.f;
		if(m_zoomLevel < 0)
			m_zoomLevel = 0;

	}


	//////////////
	// This is executed every frame at render
	///////////
	void ken01::render()
	{
		App->renderEngine->setProjection2D();

		m_mesh->getCursor()->reset()
			->translate(10, 10, 0)->scale(m_zoomLevel, m_zoomLevel, 0);

		m_mesh->render();

	}
}
