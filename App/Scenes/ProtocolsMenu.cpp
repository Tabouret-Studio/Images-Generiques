//
//  ProtocolsMenu.cpp
//  Xcode
//
//  Created by Valentin Dufois on 24/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "ProtocolsMenu.hpp"

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
	void ProtocolsMenu::load()
	{
		Scene * scene = new ProtocolsMenu();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void ProtocolsMenu::init()
	{
		rId fontID = App->ressourcesEngine->loadAsset("Karla-Bold.ttf", FONT);
		m_font = *App->ressourcesEngine->getAsset(fontID);

		m_fontSize = 100;

		m_font->loadSize(m_fontSize);

		m_interface = new Interface();

		UIButton * title = new UIButton(UI_BUTTON_TEXT, 20, 100, 410, 100);
		title->setFont(m_font, 100);
		title->setCaptionAlign(UI_TEXT_LEFT);
		title->setCaption("IMAGES GENERIQUES");

		std::vector<InstructionsProtocol *> protocols = App->generatorEngine->getProtocols();

		uint posY = 150;
		UIButton * lastProtocolBtn = nullptr;

		for(InstructionsProtocol * protocol : protocols)
		{
			//Create button
			std::string protocolName = protocol->getName();

			UIButton * protocolBtn = new UIButton(UI_BUTTON_TEXT, 20, posY, App->getWidth() - 40, 30);
			protocolBtn->setFont(m_font, 30);
			protocolBtn->setCaptionAlign(UI_TEXT_LEFT);
			protocolBtn->setCaption(protocol->getName());
			protocolBtn->setAction([protocolName, this] () -> void
			{
				ProtocolRenderer * scene = new ProtocolRenderer();
				scene->setProtocol(protocolName);
				scene->init();

				App->addScene(scene);
				App->removeScene(this);
			});

			//Add links to neighbooring buttons
			if(lastProtocolBtn != nullptr)
			{
				lastProtocolBtn->setBottomNeighboor(protocolBtn);
				protocolBtn->setTopNeighboor(lastProtocolBtn);
			}

			//Add to interface
			m_interface->addItem(protocolBtn);

			//Store for later
			m_buttons.push_back(protocolBtn);

			//Save for next loop
			lastProtocolBtn = protocolBtn;

			//Update Y position
			posY += 37;
		}

		m_interface->addItem(title);
	}


	//////////////
	// This is executed every frame before render
	///////////
	void ProtocolsMenu::execute()
	{
		if(App->appEngine->getWindow().resized == true)
			updateInterfaceDimensions();

		m_interface->execute();
	}


	//////////////
	// This is executed every frame at render
	///////////
	void ProtocolsMenu::render()
	{
		App->renderEngine->setProjection2D();

		m_interface->render();
	}

	void ProtocolsMenu::updateInterfaceDimensions()
	{
		for(UIButton * button : m_buttons)
			button->setDimensions(App->getWidth()-40, 30);
	}
}

