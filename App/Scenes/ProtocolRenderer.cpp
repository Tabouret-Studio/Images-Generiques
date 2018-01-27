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

#include "Engines/IndexEngine/IndexEngine.hpp"

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

		executeProtocol();

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

		if(App->appEngine->getKeys().ENTER)
		{
			executeProtocol();
			App->appEngine->flushKeys();
		}
		
		m_zoomLevel += App->appEngine->getMouse().scrollY / 50.f;
		if(m_zoomLevel < 0)
			m_zoomLevel = 0;

	}


	//////////////
	// This is executed every frame at render
	///////////
	void ProtocolRenderer::render()
	{
		App->renderEngine->setProjection2D();

		m_displayMesh->getCursor()->reset()
			->translate(App->getWidth()/2, App->getHeight()/2, 0)->scale(m_zoomLevel, m_zoomLevel, 0);

		m_displayMesh->render();

		m_protocolCaption->getCursor()->reset()->translate(App->getWidth()/2, App->getHeight() - 15, 0);
		m_protocolCaption->render();
	}

	void ProtocolRenderer::updateInterfaceDimensions() {}

	void ProtocolRenderer::executeProtocol()
	{
		delete m_displayMesh;
		m_displayMesh = nullptr;

		delete m_protocolCaption;
		m_protocolCaption = nullptr;

		m_svg = App->indexEngine->getRandomVectorImage();
		m_svg->applyCursor();

		VectorImage * svgTransform = m_protocol->execute({m_svg})[0];

		m_displayMesh = svgTransform->getMesh();
		m_displayMesh->generate();

		m_protocolCaption = m_font->genCaption(m_protocolName, 35);
		m_protocolCaption->generate();

		delete m_svg;
		m_svg = nullptr;

		delete svgTransform;
		svgTransform = nullptr;
	}


	ProtocolRenderer::~ProtocolRenderer()
	{
		delete m_svg;
		m_svg = nullptr;

		delete m_displayMesh;
		m_displayMesh = nullptr;

		delete m_protocolCaption;
		m_protocolCaption = nullptr;
	}
}
