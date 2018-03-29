//
//  addInstructionInterface.cpp
//  Xcode
//
//  Created by Valentin Dufois on 30/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "AddInstructionInterface.hpp"

#include "Core/AppObject.hpp"
#include "Engines/RessourcesEngine/RessourcesEngine.hpp"
#include "Engines/GeneratorEngine/GeneratorEngine.hpp"
#include "Engines/GeneratorEngine/Instructions/Instruction.hpp"

#include "Elements/Font.hpp"
#include "Elements/Mesh.hpp"

#include "Utils/Interface/Interface.hpp"
#include "Utils/Interface/UI/UIButton.hpp"

namespace Scenes
{
	void AddInstructionInterface::load()
	{
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void AddInstructionInterface::init()
	{
		rId fontID = App->ressourcesEngine->loadAsset("Karla-Bold.ttf", FONT);
		m_font = *App->ressourcesEngine->getAsset(fontID);

		m_baseInterface = new Interface();
		m_baseInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		//Scene title
		UIButton * sceneTitle = new UIButton(UI_BUTTON_TEXT, 20, 75, 0, 30);
		sceneTitle->setFont(m_font, 50);
		sceneTitle->setCaptionAlign(UI_TEXT_LEFT);
		sceneTitle->setTextColors(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1));
		sceneTitle->setCaption(u"ajouter une instruction");
		sceneTitle->setSelectable(false);

		m_baseInterface->addItem(sceneTitle);

		//Back button
		m_backButton = new UIButton(UI_BUTTON_TEXT, App->getWidth() - 170, 50, 150, 30);
		m_backButton->setFont(m_font, 30);
		m_backButton->setCaption(u"retour");
		m_backButton->setAction([this] () -> void {
			m_goback = true;
		});

		m_baseInterface->addItem(m_backButton);

		parseInstructions();

		m_listsLeftMargin = (App->getWidth() - 1000) / 2;

		displayActionsList();

		m_topSeparator = App->ressourcesEngine->gen2DTile(App->getWidth()/2, 80, App->getWidth(), 4);
		m_topSeparator->generate();

		m_bottomSeparator = App->ressourcesEngine->gen2DTile(App->getWidth()/2, App->getHeight() - 170, App->getWidth(), 4);
		m_bottomSeparator->generate();

		m_vertSeparator = App->ressourcesEngine->gen2DTile(m_listsLeftMargin + 450, 116 + (App->getHeight() - 320) / 2, 4, App->getHeight() - 333);
		m_vertSeparator->generate();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void AddInstructionInterface::execute()
	{
		m_baseInterface->execute();
		m_actionListInterface->execute();

		if(m_sourceListInterface != nullptr)
			m_sourceListInterface->execute();

		if(m_instructionConfirmInterface != nullptr)
			m_instructionConfirmInterface->execute();

		if(m_goback)
		{
			m_assemblageScene->enable();
			App->removeScene(this);
		}
	}


	//////////////
	// This is executed every time the window is resized
	///////////
	void AddInstructionInterface::onWindowResized()
	{
		//Back button
		m_backButton->setPosition(App->getWidth() - 170, 50);

		//list left margin
		m_listsLeftMargin = (App->getWidth() - 1000) / 2;

		//Separators
		m_topSeparator->getCursor()->reset()
			->translate(App->getWidth()/2, 80, 0)
			->scale(App->getWidth(), 4, 0);

		m_bottomSeparator->getCursor()->reset()
			->translate(App->getWidth()/2, App->getHeight() - 170, 0)
			->scale(App->getWidth(), 4, 0);

		m_vertSeparator->getCursor()->reset()
			->translate(m_listsLeftMargin + 450, 116 + (App->getHeight() - 320) / 2, 0)
			->scale(4, App->getHeight() - 333, 0);

		//Regenerate lists
		std::u16string tempSource, tempAction;

		displayActionsList();

		if(m_currentAction == u"")
			return;

		tempAction = m_currentAction;
		m_currentAction = u"";

		tempSource = m_currentSource;
		m_currentSource = u"";

		displaySourcesList(m_currentAction);

		if(tempSource == u"")
			return;

		displayConfirm(m_currentAction, tempSource);
	}


	//////////////
	// This is executed every frame at render
	///////////
	void AddInstructionInterface::render()
	{
		m_baseInterface->render();
		m_actionListInterface->render();

		if(m_sourceListInterface != nullptr)
			m_sourceListInterface->render();

		if(m_instructionConfirmInterface != nullptr)
			m_instructionConfirmInterface->render();

		m_topSeparator->render();
		m_bottomSeparator->render();
		m_vertSeparator->render();
	}

	void AddInstructionInterface::parseInstructions()
	{
		std::map<std::string, Instruction *> instructions = App->generatorEngine->getAllInstructions();

		//Parse all possible actions

		//! Assume no duplicate <action, source> pair in instructions
		for(const std::pair<std::string, Instruction *> &in : instructions)
		{
			if(in.second->getAction() == u"indexer")
				continue; //Ignore index instructions

			if(m_instructionsLists.find(in.second->getAction()) == m_instructionsLists.end())
			{
				//Action is absent in current list

				//Create action map
				std::map<std::u16string, std::string> action;
				action[in.second->getSourceName()] = in.first;

				//Insert in source map
				m_instructionsLists[in.second->getAction()] = action;

				continue;
			}

			//Action is present in lists
			//just insert in source map
			m_instructionsLists[in.second->getAction()][in.second->getSourceName()] = in.first;
		}

		//Parsing done ! All instructions are now referenced;
		//Delete all instructions used for parsing
		for(const std::pair<std::string, Instruction *> &in : instructions)
		{
			delete in.second;
		}
	}

	void AddInstructionInterface::displayActionsList()
	{
		delete m_actionListInterface; m_actionBtn = nullptr;
		m_actionListInterface = new Interface();
		m_actionListInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		delete m_sourceListInterface; m_sourceListInterface = nullptr;  m_sourceBtn = nullptr;
		delete m_instructionConfirmInterface; m_instructionConfirmInterface = nullptr;

		m_currentSource = u"";
		m_currentAction = u"";

		uint posY = 150;

		for(const std::pair<std::u16string, std::map<std::u16string, std::string>> &action : m_instructionsLists)
		{
			std::u16string actionName = action.first;
			UIButton * actionBtn = new UIButton(UI_BUTTON_TEXT, m_listsLeftMargin, posY, 450, 30);
			actionBtn->setFont(m_font, 30);
			actionBtn->setCaptionAlign(UI_TEXT_LEFT);
			actionBtn->setCaption(u" " + actionName);
			actionBtn->setAction([this, actionName, actionBtn] () -> void {
				displaySourcesList(actionName);

				if(m_actionBtn != nullptr)
				{
					m_actionBtn->setBackColors(glm::vec4(1, 1, 1, 0), glm::vec4(0, 0, 0, 1));
					m_actionBtn->setTextColors(glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1));
				}

				actionBtn->setBackColors(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1));
				actionBtn->setTextColors(glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1));

				m_actionBtn = actionBtn;
			});

			m_actionListInterface->addItem(actionBtn);

			posY += 40;
		}
	}

	void AddInstructionInterface::displaySourcesList(const std::u16string &action)
	{
		if(m_currentAction == action)
			return;

		delete m_sourceListInterface; m_sourceBtn = nullptr;
		delete m_instructionConfirmInterface; m_instructionConfirmInterface = nullptr;

		m_currentSource = u"";

		uint posY = 150;

		m_sourceListInterface = new Interface();
		m_sourceListInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		for(const std::pair<std::u16string, std::string> &source : m_instructionsLists[action])
		{
			std::u16string sourceName = source.first;

			UIButton * sourceBtn = new UIButton(UI_BUTTON_TEXT, m_listsLeftMargin + 452, posY, 558, 30);
			sourceBtn->setFont(m_font, 30);
			sourceBtn->setCaptionAlign(UI_TEXT_LEFT);
			sourceBtn->setCaption(u" " + sourceName);
			sourceBtn->setAction([this, action, sourceName, sourceBtn] () -> void {
				displayConfirm(action, sourceName);

				if(m_sourceBtn != nullptr)
				{
					m_sourceBtn->setBackColors(glm::vec4(1, 1, 1, 0), glm::vec4(0, 0, 0, 1));
					m_sourceBtn->setTextColors(glm::vec4(0, 0, 0, 1), glm::vec4(1, 1, 1, 1));
				}

				sourceBtn->setBackColors(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1));
				sourceBtn->setTextColors(glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1));
				m_sourceBtn = sourceBtn;
			});

			m_sourceListInterface->addItem(sourceBtn);

			posY += 40;
		}

		delete m_instructionConfirmInterface;
		m_instructionConfirmInterface = nullptr;
	}

	void AddInstructionInterface::displayConfirm(const std::u16string &action, const std::u16string &source)
	{
		if(m_currentAction == action && m_currentSource == source)
			return;

		m_currentSource = source;

		// Erase old interface
		delete m_instructionConfirmInterface;
		m_instructionConfirmInterface = new Interface();
		m_instructionConfirmInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		std::string instructionID = m_instructionsLists[action][source];

		// Get instruction name
		Instruction * instruction = App->generatorEngine->getInstruction(instructionID);
		std::u16string instructionTextName = instruction->getFullName();

		delete instruction;

		//Instruction name
		UIButton * sceneTitle = new UIButton(UI_BUTTON_TEXT, 0, App->getHeight() - 100, App->getWidth(), 30);
		sceneTitle->setFont(m_font, 30);
		sceneTitle->setCaption(instructionTextName);
		sceneTitle->setSelectable(false);

		m_instructionConfirmInterface->addItem(sceneTitle);

		UIButton * addInstruction = new UIButton(UI_BUTTON_TEXT, App->getWidth() / 2 - 125, App->getHeight() - 50, 250, 30);
		addInstruction->setFont(m_font, 30);
		addInstruction->setCaption(u"- ajouter -");
		addInstruction->setAction([this, instructionID] () -> void {
			addInstructionAndQuit(instructionID);
		});

		m_instructionConfirmInterface->addItem(addInstruction);
	}

	void AddInstructionInterface::addInstructionAndQuit(const std::string &instruction)
	{
		m_assemblageScene->addInstruction(instruction);
		m_goback = true;
	}

	AddInstructionInterface::~AddInstructionInterface()
	{
		delete m_baseInterface;
		delete m_sourceListInterface;
		delete m_actionListInterface;
		delete m_instructionConfirmInterface;
		delete m_topSeparator;
		delete m_bottomSeparator;
		delete m_vertSeparator;
	}
}
