//
//  txt.cpp
//  Xcode
//
//  Created by Valentin Dufois on 24/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "txt.hpp"

#include "Elements/Font.hpp"
#include "Elements/Mesh.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

#include "Engines/RessourcesEngine/Exporters/SVGExporter.hpp"
#include "Engines/RessourcesEngine/Exporters/VectorImagesToJSONExporter.hpp"
#include "Engines/RessourcesEngine/Importers/JSONToVectorImagesImporter.hpp"

#include "Engines/GeneratorEngine/GeneratorEngine.hpp"
#include "Engines/GeneratorEngine/InstructionsProtocol/InstructionsProtocol.hpp"
#include "Utils/SDL.hpp"

namespace Scenes
{
	void txt::load()
	{
		Scene * scene = new txt();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void txt::init()
	{
		rId fontID = App->ressourcesEngine->loadAsset("Karla-Bold.ttf", FONT);
		m_font = *App->ressourcesEngine->getAsset(fontID);

		m_font->setHeight(50.0);
		m_font->generate();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void txt::execute()
	{
		m_mesh = m_font->genCaption("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ");
		//m_mesh = m_font->genCaption(std::to_string(SDL::getWindowDPI()));
		m_mesh->generate();
		m_mesh->getCursor()->translate(App->getWidth() / 2, App->getHeight() / 2, 0);


		m_line = VectorImage(Shape(Bezier(0, App->getHeight()/2, 0, App->getHeight()/2, App->getWidth(), App->getHeight()/2, App->getWidth(), App->getHeight()/2))).getMesh();

		//m_line->generate();
	}


	//////////////
	// This is executed every frame at render
	///////////
	void txt::render()
	{
		App->renderEngine->setProjection2D();
		m_mesh->render();
		//m_line->render();

		m_mesh->freeTexture();
		delete m_mesh;
		delete m_line;
	}
}

