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

#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"

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
		rId svgID = App->ressourcesEngine->loadAsset("ml.svg", VECTOR);
		m_svg = *App->ressourcesEngine->getAsset(svgID);

		//Instructions
		InstructionsProtocol protocol({
			INSTRUCTION_PATHS_ORDER_RANDOMIZER,
			INSTRUCTION_PATHS_CHAINING
		});

		VectorImage * imageTransformed = protocol.execute({m_svg})[0];

		//Export
		SVGExporter exporter;
		exporter.exportSVG(imageTransformed, "testInstruction");

		//Generate and display Mesh
		m_mesh = imageTransformed->getMesh();

		m_mesh->generate();
		m_mesh->setRenderFormat(GL_POINTS);
		m_mesh->getCursor()
			->translate(App->getWidth()/2, App->getHeight()/2, 0);
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
