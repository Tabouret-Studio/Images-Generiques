//
//  Gen01.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Gen01.hpp"

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
		//Loading
		rId svgID = App->ressourcesEngine->loadAsset("handComputer.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);
		
		//Instructions
		InstructionsProtocol protocol({
			"PATHS_ORDER_RANDOMIZER",
			"PATHS_CHAINING",
			"TEST_TEST_TEST"
		});

		VectorImage * imageTransformed = protocol.execute({m_svg})[0];

		//Export
		SVGExporter exporter;
		exporter.exportSVG(imageTransformed, "testInstruction");

		//Generate and display Mesh
		//m_mesh = m_svg->getMesh();

		m_mesh = m_svg->getMesh();

		m_mesh->generate();
		m_mesh->setRenderFormat(GL_POINTS);

		glPointSize(5);

		//m_mesh->getCursor()
		//	->reset()->translate(App->getWidth()/2, App->getHeight()/2, 1);

		m_mesh->getCursor()->reset();
		m_mesh->applyCursor();
		m_mesh->getCursor()->rotate(180, 1, 0, 0)->translate(0, 0, (m_svg->getHeight() / 2.f));

	}


	//////////////
	// This is executed every frame before render
	///////////
	void Gen01::execute()
	{
		m_mesh->getCursor()->rotate(1, 0, 1, 0);

		//float scrollAmount = App->appEngine->getMouse().scrollY/10.0f;
		//m_mesh->getCursor()->scale(1+scrollAmount, 1+scrollAmount, 1);

	}


	//////////////
	// This is executed every frame at render
	///////////
	void Gen01::render()
	{
		App->renderEngine->setProjection3D();
		m_mesh->render();
	}
}
