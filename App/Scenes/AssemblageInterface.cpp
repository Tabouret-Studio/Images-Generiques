//
//  AssemblageInterface.cpp
//  Xcode
//
//  Created by Valentin Dufois on 29/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "AssemblageInterface.hpp"

#include "Core/AppObject.hpp"

#include "Engines/RessourcesEngine/RessourcesEngine.hpp"

#include "Engines/GeneratorEngine/InstructionsProtocol/InstructionsProtocol.hpp"

#include "Elements/Mesh.hpp"
#include "Elements/Font.hpp"

#include "Utils/Utils.hpp"
#include "Utils/Interface/Interface.hpp"
#include "Utils/Interface/UI/UIButton.hpp"

#include <algorithm>

namespace Scenes
{
	void AssemblageInterface::load()
	{
		Scene * scene = new AssemblageInterface();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void AssemblageInterface::init()
	{
		m_workArea = glm::vec2(800, 600);

		rId fontID = App->ressourcesEngine->loadAsset("Karla-Bold.ttf", FONT);
		m_font = *App->ressourcesEngine->getAsset(fontID);

		m_baseInterface = new Interface();
		m_baseInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		//Scene title
		UIButton * sceneTitle = new UIButton(UI_BUTTON_TEXT, 20, 75, 150, 30);
		sceneTitle->setFont(m_font, 50);
		sceneTitle->setCaptionAlign(UI_TEXT_LEFT);
		sceneTitle->setTextColors(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1));
		sceneTitle->setCaption("ASSEMBLAGE");
		sceneTitle->setSelectable(false);
		sceneTitle->setAction(nullptr);

		m_baseInterface->addItem(sceneTitle);

		//Add instruction button
		m_addInstructionBtn = new UIButton(UI_BUTTON_TEXT, 420, 0, 175, 30);
		m_addInstructionBtn->setFont(m_font, 30);
		m_addInstructionBtn->setCaption("AJOUTER +");

		m_baseInterface->addItem(m_addInstructionBtn);

		//PlayPause Btn
		m_playPauseBtn = new UIButton(UI_BUTTON_TEXT, 455, 50, 125, 30);
		m_playPauseBtn->setFont(m_font, 30);
		m_playPauseBtn->setCaption("PAUSE");
		m_playPauseBtn->setAction([this] () -> void {
			if(m_playing)
			{
				m_playing = false;
				m_playPauseBtn->setCaption("PLAY");
				return;
			}

			m_playing = true;
			m_playPauseBtn->setCaption("PAUSE");
		});

		m_baseInterface->addItem(m_playPauseBtn);

		//Reset Btn
		m_resetBtn = new UIButton(UI_BUTTON_TEXT, 10, 0, 175, 20);
		m_resetBtn->setFont(m_font, 20);
		m_resetBtn->setCaption("RECOMMENCER");
		m_resetBtn->setAction([this] () -> void {
			resetLoop();
		});

		m_baseInterface->addItem(m_resetBtn);

		m_protocol = new InstructionsProtocol({
			"PATHS_ORDER_RANDOMIZER",
			"PATHS_GEOMETRY_NOISETRANSLATE",
			"PATHS_GEOMETRY_NOISEROTATE",
			"PATHS_GEOMETRY_SQUARIFY"
		});

		m_vertSeparator = App->ressourcesEngine->gen2DTile(598, App->getHeight()/2, 4, App->getHeight());
		m_vertSeparator->generate();

		generateInstructionList();

		//Load renderer
		m_renderer = new SimpleRenderer();
		m_renderer->setBounds(600, 0, 0, 0);
		m_renderer->init();
		App->addScene(m_renderer);

		//prepare loop
		initLoop();
		resetLoop();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void AssemblageInterface::execute()
	{
		m_baseInterface->execute();
		m_instructionsInterface->execute();

		if(m_reloadList)
			generateInstructionList();

		protocolLoop();
	}


	//////////////
	// This is executed every frame at render
	///////////
	void AssemblageInterface::render()
	{
		//Interface
		m_baseInterface->render();
		m_instructionsInterface->render();

		for(Mesh * mesh : m_lines)
			mesh->render();

		m_vertSeparator->render();

		//Display arrow only if instructions are present
		if(m_protocol->getInstructionsInOrder().size() > 0)
			m_loopCursor->render();
	}

	void AssemblageInterface::generateInstructionList()
	{
		delete m_instructionsInterface;

		for(Mesh * mesh : m_lines)
			delete mesh;
		m_lines.clear();

		m_instructionsInterface = new Interface();
		m_instructionsInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		int posY = 150;

		std::vector<std::string> instructionNames = m_protocol->getInstructionsInOrder();

		uint i = 0;
		for(std::vector<std::string>::const_iterator instructionName = instructionNames.begin(); instructionName != instructionNames.end(); ++instructionName, ++i)
		{
			std::vector<std::string> decomposedName = Utils::decomposeByDelimiter(*instructionName, "_");

			//Remove Button
			UIButton * instructionRemoveBtn = new UIButton(UI_BUTTON_TEXT, 10, posY, 30, 30);
			instructionRemoveBtn->setFont(m_font, 30);
			instructionRemoveBtn->setCaption("X");
			instructionRemoveBtn->setAction([this, i] () -> void {
				m_protocol->removeInstruction(i);
				m_reloadList = true;
			});

			m_instructionsInterface->addItem(instructionRemoveBtn);

			//Instruction name
			UIButton * instructionBtn = new UIButton(UI_BUTTON_TEXT, 50, posY-7, 425, 30);
			instructionBtn->setFont(m_font, 24);
			instructionBtn->setCaptionAlign(UI_TEXT_LEFT);
			instructionBtn->setCaption(decomposedName[0] + " " + decomposedName[1] + " " + decomposedName[2]);
			instructionBtn->setSelectable(false);

			m_instructionsInterface->addItem(instructionBtn);

			if(i != 0)
			{
				//Move up Button
				UIButton * instructionUpBtn = new UIButton(UI_BUTTON_TEXT, 535, posY, 30, 30);
				instructionUpBtn->setFont(m_font, 30);
				instructionUpBtn->setCaption("U");
				instructionUpBtn->setAction([this, i] () -> void {
					m_protocol->swapInstructions(i-1, i);
					m_reloadList = true;
				});

				m_instructionsInterface->addItem(instructionUpBtn);
			}

			if(i != instructionNames.size()-1)
			{
				//Move down Button
				UIButton * instructionDownBtn = new UIButton(UI_BUTTON_TEXT, 565, posY, 30, 30);
				instructionDownBtn->setFont(m_font, 30);
				instructionDownBtn->setCaption("D");
				instructionDownBtn->setAction([this, i] () -> void {
					m_protocol->swapInstructions(i, i+1);
					m_reloadList = true;
				});

				m_instructionsInterface->addItem(instructionDownBtn);
			}

			//*BEAUTIFUL* line
			Mesh * line = App->ressourcesEngine->gen2DTile(300, posY + 12, 600, 4);
			line->generate();

			m_lines.push_back(line);

			posY += 45;
		}

		//Update end-of-list buttons
		m_addInstructionBtn->setPosition(370, posY + 30);
		m_resetBtn->setPosition(10, posY + 30);

		m_reloadList = false;
	}

	void AssemblageInterface::initLoop()
	{
		//Create arrow
		std::vector<Vertex> arrow;
		arrow.push_back(Vertex(glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 0.0)));
		arrow.push_back(Vertex(glm::vec3(0.0,-1.0, 0.0), glm::vec2(1.0, 0.0)));
		arrow.push_back(Vertex(glm::vec3(0.75, 0.0, 0.0), glm::vec2(1.0, 1.0)));

		m_loopCursor = new Mesh(arrow);
		m_loopCursor->setColor(glm::vec4(0, 0, 0, 1));
		m_loopCursor->getCursor()->scale(22.5, 22.5, 0);
		m_loopCursor->applyCursor();
		m_loopCursor->getCursor()->translate(-1000, -1000, 0);
		m_loopCursor->setProgram(App->getDefaultProgram());
		m_loopCursor->generate();
	}

	void AssemblageInterface::resetLoop()
	{
		m_lastIter = std::chrono::steady_clock::now() - std::chrono::duration<int>(100);

		delete m_workingImage;

		rId svgID = App->ressourcesEngine->loadAsset("github.svg", VECTOR);
		m_workingImage = new VectorImage(*App->ressourcesEngine->getAsset(svgID)); //Copy constructor

		sendToRenderer(m_workingImage);

		m_loopCursor->getCursor()->reset()->translate(600, 140, 0);

		m_nextInstruction = 0;
	}

	void AssemblageInterface::protocolLoop()
	{
		uint iterationInterval = 1; //seconds

		//Are we paused ?
		if(!m_playing)
			return; //Animation paused

		//Is interval OK ?
		if(std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - m_lastIter).count() < iterationInterval)
			return; //Too soon

		uint protocolSize = (uint)m_protocol->getInstructionsInOrder().size();

		//Is there any instruction to use ?
		if(protocolSize == 0)
			return; //Protocol is empty

		//Set instruction to use (avoid going out of loop
		if(m_nextInstruction >= protocolSize)
			m_nextInstruction = 0;

		//Get instruction to use
		std::string instructionName = m_protocol->getInstructionsInOrder()[m_nextInstruction];
		InstructionObject * instruction = m_protocol->getInstructions()[instructionName];

		//Pass parameters
		//TODO

		//Execute instruction
		VectorImage * tempImage = instruction->execute({m_workingImage})[0];
		delete m_workingImage;
		m_workingImage = tempImage;

		//Send image to renderer
		sendToRenderer(m_workingImage);

		//Update arrow position
		m_loopCursor->getCursor()->reset()->translate(600, 140 + float(m_nextInstruction) * 45, 0);

		//Increment instruction
		m_nextInstruction++;

		//Reset interval timer
		m_lastIter = std::chrono::steady_clock::now();
	}

	void AssemblageInterface::sendToRenderer(VectorImage * vectorImage)
	{
		VectorImage * tempImage = new VectorImage(*vectorImage);
		tempImage->applyCursor();

		delete m_workingMesh;
		m_workingMesh = tempImage->getMesh();
		m_renderer->setMesh(m_workingMesh);

		delete tempImage;
	}

	AssemblageInterface::~AssemblageInterface()
	{
		delete m_baseInterface;
		delete m_instructionsInterface;
		delete m_protocol;
		delete m_loopCursor;
		delete m_workingMesh;
	}
}
