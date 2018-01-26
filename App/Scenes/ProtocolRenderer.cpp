//
//  ProtocolRenderer.cpp
//  Xcode
//
//  Created by Valentin Dufois on 26/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ProtocolRenderer.hpp"

#include "Elements/Font.hpp"
#include "Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

#include "Utils/Interface/Interface.hpp"
#include "Utils/Interface/UI/UIButton.hpp"

#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"
#include "Engines/RessourcesEngine/Exporters/VectorImagesToJSONExporter.hpp"
#include "Engines/RessourcesEngine/Importers/JSONToVectorImagesImporter.hpp"

#include "Engines/GeneratorEngine/GeneratorEngine.hpp"
#include "Engines/GeneratorEngine/InstructionsProtocol/InstructionsProtocol.hpp"
#include "Utils/SDL.hpp"

namespace Scenes
{
	void ProtocolRenderer::load()
	{
		Scene * scene = new ProtocolRenderer();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void ProtocolRenderer::init()
	{
		rId fontID = App->ressourcesEngine->loadAsset("Karla-Bold.ttf", FONT);
		m_font = *App->ressourcesEngine->getAsset(fontID);

		m_protocol = App->generatorEngine->getProtocol(m_protocolName);

		rId svgID = App->ressourcesEngine->loadAsset("github.svg", VECTOR);
		VectorImage * m_svg = *App->ressourcesEngine->getAsset(svgID);

		m_displayMesh = m_protocol->execute({m_svg})[0]->getMesh();
		m_displayMesh->generate();
		m_displayMesh->getCursor()->translate(App->getWidth()/2, App->getHeight()/2, 0);

		m_zoomLevel = 1;
	}


	//////////////
	// This is executed every frame before render
	///////////
	void ProtocolRenderer::execute()
	{
		if(App->appEngine->getWindow().resized == true)
			updateInterfaceDimensions();

		if(App->appEngine->getKeys().ESC)
		{
			ProtocolsMenu::load();
			App->removeScene(this);
		}

		m_zoomLevel += App->appEngine->getMouse().scrollY / 50.f;

	}


	//////////////
	// This is executed every frame at render
	///////////
	void ProtocolRenderer::render()
	{
		App->renderEngine->setProjection2D();

		m_displayMesh->getCursor()->reset()
			->translate(App->getWidth()/2, App->getHeight()/2, 0)
			->scale(m_zoomLevel, m_zoomLevel, 0);
		
		m_displayMesh->render();
	}

	void ProtocolRenderer::updateInterfaceDimensions()
	{
	}
}
