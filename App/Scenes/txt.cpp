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

		m_fontSize = 100;

		m_font->loadSize(m_fontSize);

		m_interface = new Interface();

		UIButton * button = new UIButton(UI_BUTTON_TEXT, App->getWidth()/2 - 200, App->getHeight()/2 - 75, 410, 100);
		button->setFont(m_font, 100);
		button->setCaption("IMAGES");

		UIButton * button2 = new UIButton(UI_BUTTON_TEXT, App->getWidth()/2, App->getHeight()/2 + 75, 400, 50);
		button2->setFont(m_font, 50);
		button2->setCaption("GENERIQUES");

		button->setNeighboors(nullptr, nullptr, button2, nullptr);
		button2->setNeighboors(button, nullptr, nullptr, nullptr);

		m_interface->addItem(button);
		m_interface->addItem(button2);
	}


	//////////////
	// This is executed every frame before render
	///////////
	void txt::execute()
	{
		m_interface->execute();
	}


	//////////////
	// This is executed every frame at render
	///////////
	void txt::render()
	{
		App->renderEngine->setProjection2D();

		m_interface->render();
	}
}

