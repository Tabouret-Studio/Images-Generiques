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
#include "Engines/GeneratorEngine/GeneratorEngine.hpp"
#include "Engines/IndexEngine/IndexEngine.hpp"
#include "Engines/AppEngine/AppEngine.hpp"

#include "Engines/GeneratorEngine/InstructionsProtocol/InstructionsProtocol.hpp"
#include "Engines/GeneratorEngine/InstructionParameters.hpp"
#include "Engines/GeneratorEngine/Instructions/Instruction.hpp"
#include "Engines/GeneratorEngine/VectorImageExcerpt.hpp"

#include "Elements/Mesh.hpp"
#include "Elements/Font.hpp"

#include "Utils/Utils.hpp"
#include "Utils/Interface/Interface.hpp"
#include "Utils/Interface/UI/UIButton.hpp"

#include <algorithm>
#include <sstream>

#define LOOP_INTERVAL .25

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
		rId fontID = App->ressourcesEngine->loadAsset("Karla-Bold.ttf", FONT);
		m_font = *App->ressourcesEngine->getAsset(fontID);

		m_baseInterface = new Interface();
		m_baseInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		//Scene title
		UIButton * sceneTitle = new UIButton(UI_BUTTON_TEXT, 20, 75, 150, 30);
		sceneTitle->setFont(m_font, 50);
		sceneTitle->setCaptionAlign(UI_TEXT_LEFT);
		sceneTitle->setTextColors(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1));
		sceneTitle->setCaption(u"assemblage");
		sceneTitle->setSelectable(false);
		sceneTitle->setAction(nullptr);

		m_baseInterface->addItem(sceneTitle);

		//Add instruction button
		m_addInstructionBtn = new UIButton(UI_BUTTON_TEXT, 420, 0, 175, 30);
		m_addInstructionBtn->setFont(m_font, 30);
		m_addInstructionBtn->setCaption(u"ajouter +");
		m_addInstructionBtn->setAction([this] () -> void {

			//Disable current interface
			disable();
			m_renderer->disable();

			//Open add interface
			AddInstructionInterface * scene = new AddInstructionInterface();
			scene->setAssemblageScene(this);
			scene->init();

			App->addScene(scene);
		});

		m_baseInterface->addItem(m_addInstructionBtn);

		// PlayPause Btn
		m_playPauseBtn = new UIButton(UI_BUTTON_TEXT, 430, 50, 150, 30);
		m_playPauseBtn->setFont(m_font, 30);
		m_playPauseBtn->setCaption(u"boucle");
		m_playPauseBtn->setAction([this] () -> void {
			toggleLoop();
		});

		m_baseInterface->addItem(m_playPauseBtn);

		// Paths index Btn
		m_pathsIndexBtn = new UIButton(UI_BUTTON_TEXT, 25, 0, 175, 20);
		m_pathsIndexBtn->setFont(m_font, 20);
		m_pathsIndexBtn->setCaption(u"index des tracés");
		m_pathsIndexBtn->setAction([this] () -> void {
			applyPathsIndex();
		});

		m_baseInterface->addItem(m_pathsIndexBtn);

		// Paths index Btn
		m_shapesIndexBtn = new UIButton(UI_BUTTON_TEXT, 25, 0, 175, 20);
		m_shapesIndexBtn->setFont(m_font, 20);
		m_shapesIndexBtn->setCaption(u"index des formes");
		m_shapesIndexBtn->setAction([this] () -> void {
			applyShapesIndex();
		});

		m_baseInterface->addItem(m_shapesIndexBtn);

		// Reset Btn
		m_resetBtn = new UIButton(UI_BUTTON_TEXT, 25, 0, 175, 20);
		m_resetBtn->setFont(m_font, 20);
		m_resetBtn->setCaption(u"recommencer");
		m_resetBtn->setAction([this] () -> void {
			resetLoop();
		});

		m_baseInterface->addItem(m_resetBtn);

		// Save Btn
		m_saveSVGBtn = new UIButton(UI_BUTTON_TEXT, App->getWidth() - 185, App->getHeight() - 20, 175, 20);
		m_saveSVGBtn->setFont(m_font, 20);
		m_saveSVGBtn->setCaption(u"enregistrer");
		m_saveSVGBtn->setAction([this] () -> void {
			saveWorkingImage();
		});

		m_baseInterface->addItem(m_saveSVGBtn);

		//Paths count
		m_pathsCount = new UIButton(UI_BUTTON_TEXT, 10, App->getHeight() - 17, 175, 20);
		m_pathsCount->setFont(m_font, 20);
		m_pathsCount->setCaptionAlign(UI_TEXT_LEFT);
		m_pathsCount->setSelectable(false);

		m_baseInterface->addItem(m_pathsCount);
		m_pathsCount->hide();

		//Protocol elements
		m_protocol = new InstructionsProtocol();

		m_vertSeparator = App->ressourcesEngine->gen2DTile(598, App->getHeight()/2, 4, App->getHeight());
		m_vertSeparator->generate();

		m_upArrowTexID = App->ressourcesEngine->loadAsset("arrowUp.png", IMAGE);
		m_upArrowTexIDSelected = App->ressourcesEngine->loadAsset("arrowUpSelected.png", IMAGE);

		m_downArrowTexID = App->ressourcesEngine->loadAsset("arrowDown.png", IMAGE);
		m_downArrowTexIDSelected = App->ressourcesEngine->loadAsset("arrowDownSelected.png", IMAGE);

		m_deleteTexID = App->ressourcesEngine->loadAsset("delete.png", IMAGE);
		m_deleteTexIDSelected = App->ressourcesEngine->loadAsset("deleteSelected.png", IMAGE);

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
		// Check keyboard events
		// TODO: Handle keyboard event with designated methods like `onKeyPressed`
		//		  defined in Scene sueprclass
		if(App->appEngine->getKeys().ENTER)
		{
			m_showInterface = !m_showInterface;
			App->toggleFullScreen();

			if(m_showInterface)
				m_renderer->setBounds(600, 0, 0, 0);
			else
				m_renderer->setBounds(0, 0, 0, 0);
		}

		if(App->appEngine->getKeys().SPACE)
		{
			toggleLoop();
		}

		if(App->appEngine->getKeys().S)
		{
			saveWorkingImage();
		}

		App->appEngine->flushKeys();

		// Execute the loop actions
		m_baseInterface->execute();

		if(m_showInterface)
			m_instructionsInterface->execute();

		if(m_reloadList)
			generateInstructionList();

		protocolLoop();
	}


	//////////////
	// This is executed every time the window is resized
	///////////
	void AssemblageInterface::onWindowResized()
	{
		m_vertSeparator->getCursor()->reset()
			->translate(598, App->getHeight() /2, 0)
			->scale(4, App->getHeight(), 0);

		m_saveSVGBtn->setPosition(App->getWidth() - 185, App->getHeight() - 20);
	}


	//////////////
	// This is executed every frame at render
	///////////
	void AssemblageInterface::render()
	{
		//Make sure renderer is active
		m_renderer->enable();

		if(!m_showInterface)
			return;

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

	void AssemblageInterface::toggleLoop()
	{
		if(m_playing)
		{
			m_playing = false;
			m_playPauseBtn->setCaption(u"boucle");
			return;
		}

		m_playing = true;
		m_playPauseBtn->setCaption(u"pause");
	}

	void AssemblageInterface::generateInstructionList()
	{
		delete m_instructionsInterface;

		for(Mesh * mesh : m_lines)
			delete mesh;

		m_lines.clear();

		m_instructionsInterface = new Interface();
		m_instructionsInterface->setInteractionFormat(INTERFACE_INTERACTIONS_MOUSE);

		uint posY = 150;

		std::vector<std::string> instructionNames = m_protocol->getInstructionsInOrder();

		if(instructionNames.size() == 0)
		{
			UIButton * emptyProtocol = new UIButton(UI_BUTTON_TEXT, 45, posY-13, 425, 30);
			emptyProtocol->setFont(m_font, 20);
			emptyProtocol->setCaptionAlign(UI_TEXT_LEFT);
			emptyProtocol->setCaption(u"l'assemblage est vide");
			emptyProtocol->setSelectable(false);
			
			m_instructionsInterface->addItem(emptyProtocol);

			posY += 45;
		}
		else
		{
			uint i = 0;
			for(std::vector<std::string>::const_iterator instructionName = instructionNames.begin(); instructionName != instructionNames.end(); ++instructionName, ++i)
			{
				generateInstructionLine(*instructionName, posY, i, instructionNames);
			}
		}

		//Update end-of-list buttons
		m_addInstructionBtn->setPosition(370, posY + 30);
		m_pathsIndexBtn->setPosition(25, posY + 15);
		m_shapesIndexBtn->setPosition(25, posY + 40);
		m_resetBtn->setPosition(25, posY + 65);

		m_reloadList = false;
	}

	void AssemblageInterface::generateInstructionLine(const std::string &instructionName, uint &posY, const uint &i, const std::vector<std::string> &instructionNames)
	{
		Instruction * instruction = App->generatorEngine->getInstruction(instructionName);
		//InstructionParameters * iParams = m_protocol->getParameters(i);

		//Remove Button
		UIButton * instructionRemoveBtn = new UIButton(UI_BUTTON_TEXT, 10, posY + 12, 30, 30);
		instructionRemoveBtn->setFont(m_font, 30);
		instructionRemoveBtn->setCaption(u"X");
		instructionRemoveBtn->setAction([this, i] () -> void {
			m_protocol->removeInstruction(i);
			m_reloadList = true;
		});
		instructionRemoveBtn->setTextures(m_deleteTexID, m_deleteTexIDSelected);

		m_instructionsInterface->addItem(instructionRemoveBtn);

		std::u16string instructionTextName = instruction->getFullName();

		//Instruction name
		UIButton * instructionBtn = new UIButton(UI_BUTTON_TEXT, 45, posY+10, 425, 30);
		instructionBtn->setFont(m_font, 30);
		instructionBtn->setCaptionAlign(UI_TEXT_LEFT);
		instructionBtn->setCaption(instructionTextName);
		instructionBtn->setSelectable(false);

		m_instructionsInterface->addItem(instructionBtn);

		if(i != 0)
		{
			//Move up Button
			UIButton * instructionUpBtn = new UIButton(UI_BUTTON_TEXT, 535, posY + 12, 30, 30);
			instructionUpBtn->setFont(m_font, 30);
			instructionUpBtn->setCaption(u"+");
			instructionUpBtn->setAction([this, i] () -> void {
				m_protocol->swapInstructions(i-1, i);
				m_reloadList = true;
			});
			instructionUpBtn->setTextures(m_upArrowTexID, m_upArrowTexIDSelected);

			m_instructionsInterface->addItem(instructionUpBtn);
		}

		if(i != instructionNames.size()-1)
		{
			//Move down Button
			UIButton * instructionDownBtn = new UIButton(UI_BUTTON_TEXT, 565, posY + 12, 30, 30);
			instructionDownBtn->setFont(m_font, 30);
			instructionDownBtn->setCaption(u"-");
			instructionDownBtn->setAction([this, i] () -> void {
				m_protocol->swapInstructions(i, i+1);
				m_reloadList = true;
			});
			instructionDownBtn->setTextures(m_downArrowTexID, m_downArrowTexIDSelected);

			m_instructionsInterface->addItem(instructionDownBtn);
		}

		posY += 20;

		//Intensity controls

		/*
		//Intensity label
		UIButton * intensityLabel = new UIButton(UI_BUTTON_TEXT, 67, posY, 30, 15);
		intensityLabel->setFont(m_font, 15);
		intensityLabel->setCaption(u"intensité");
		intensityLabel->setSelectable(false);

		m_instructionsInterface->addItem(intensityLabel);

		//Intensity value
		std::string value8 = floatToString(iParams->getParam("intensity"));
		std::u16string value16(value8.begin(), value8.end());

		UIButton * intensityValue = new UIButton(UI_BUTTON_TEXT, 144, posY, 30, 15);
		intensityValue->setFont(m_font, 15);
		intensityValue->setCaption(value16);
		intensityValue->setSelectable(false);

		m_instructionsInterface->addItem(intensityValue);
		
		UIButton * intensityDownBtn = new UIButton(UI_BUTTON_TEXT, 127, posY, 15, 15);
		intensityDownBtn->setFont(m_font, 15);
		intensityDownBtn->setCaption(u"-");
		intensityDownBtn->setAction([this, i, intensityValue] () -> void
		{
			float intensity = m_protocol->getParameters(i)->getParam("intensity") - .1f;

			if(intensity < 0)
				intensity = 0;

			m_protocol->getParameters(i)->updateParam("intensity", intensity);

			std::string value8 = floatToString(intensity);
			std::u16string value16(value8.begin(), value8.end());

			intensityValue->setCaption(value16);
		});

		//Intensity down button
		UIButton * intensityUpBtn = new UIButton(UI_BUTTON_TEXT, 177, posY, 15, 15);
		intensityUpBtn->setFont(m_font, 15);
		intensityUpBtn->setCaption(u"+");
		intensityUpBtn->setAction([this, i, intensityValue] () -> void
		{
			float intensity = m_protocol->getParameters(i)->getParam("intensity") + .1f;
			m_protocol->getParameters(i)->updateParam("intensity", intensity);

			std::string value8 = floatToString(intensity);
			std::u16string value16(value8.begin(), value8.end());

			intensityValue->setCaption(value16);
		});

		m_instructionsInterface->addItem(intensityUpBtn);

		m_instructionsInterface->addItem(intensityDownBtn);
		*/

		//*BEAUTIFUL* line
		Mesh * line = App->ressourcesEngine->gen2DTile(300, posY + 12, 600, 4);
		line->generate();

		m_lines.push_back(line);

		posY += 45;

		delete instruction;
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

		//reset working image
		delete m_workingImage;
		delete m_savedImage;

		//Static load
		//rId svgID = App->ressourcesEngine->loadAsset("enfant_machine.svg", VECTOR);
		//m_workingImage = new VectorImage(*App->ressourcesEngine->getAsset(svgID)); //Copy constructor

		//Dynamic load from index
		m_workingImage = App->indexEngine->getRandomVectorImage();
		m_savedImage = new VectorImage(m_workingImage);

		//m_workingImage = m_font->genOutlines(u"é");

		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		m_loopCursor->getCursor()->reset()->translate(600, 150, 0);

		std::string count = std::to_string(m_workingImage->getBeziers().size());
		m_pathsCount->setCaption(std::u16string(count.begin(), count.end()));

		m_nextInstruction = 0;
	}

	void AssemblageInterface::protocolLoop()
	{
		float iterationInterval = LOOP_INTERVAL; //seconds

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

		//Check for end of loop
		if(m_nextInstruction + 1 > protocolSize)
		{
			//End of loop
			m_nextInstruction = 0;

			//m_workingImage = m_excerpter->replaceExcerpt(m_excerpt, EXCERPT_BEZIER);
			//delete m_excerpt;
		}

		if(m_nextInstruction == 0)
		{
			//Beginning of loop
			//m_excerpter = new VectorImageExcerpt(m_workingImage);
			//m_excerpt = m_excerpter->getExcerpt(EXCERPT_BEZIER);
		}

		//Get instruction to use
		std::string instructionName = m_protocol->getInstructionsInOrder()[m_nextInstruction];
		InstructionObject * instruction = m_protocol->getInstructions()[instructionName];
		instruction->setParameters(m_protocol->getParameters(m_nextInstruction));

		//Execute instruction
		//std::vector<VectorImage *> images = {m_excerpt};
		//m_excerpt = instruction->execute(images)[0];

		std::vector<VectorImage *> images = {m_workingImage};
		m_workingImage = instruction->execute(images)[0];

		delete m_savedImage;
		m_savedImage = new VectorImage(m_workingImage);

		//Send images to renderer
		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		std::string count = std::to_string(m_workingImage->getBeziers().size());
		m_pathsCount->setCaption(std::u16string(count.begin(), count.end()));

		//Update arrow position
		m_loopCursor->getCursor()->reset()->translate(600, 150 + float(m_nextInstruction) * 65, 0);

		//Increment instruction
		m_nextInstruction++;

		//Reset interval timer
		m_lastIter = std::chrono::steady_clock::now();
	}

	void AssemblageInterface::saveWorkingImage()
	{
		App->indexEngine->insertVectorImage(m_workingImage, {"export", "loop"});
	}

	void AssemblageInterface::sendToRenderer(VectorImage * vectorImage, const uint &pointSize)
	{
		VectorImage tempImage = *vectorImage;
		tempImage.applyCursor();

		delete m_workingMesh;
		m_workingMesh = tempImage.getMesh();
		m_workingMesh->setPointSize(pointSize);
		m_renderer->addMesh(m_workingMesh);
	}

	void AssemblageInterface::addInstruction(const std::string &instruction)
	{
		m_protocol->addInstruction(instruction);
		uint instructionID = (uint)m_protocol->getInstructionsInOrder().size() - 1;

		InstructionParameters * params = new InstructionParameters();
		params->createParam("intensity", 1.0);

		m_protocol->bindParameter(instructionID, params);

		m_reloadList = true;
		onWindowResized();
	}

	void AssemblageInterface::applyPathsIndex()
	{
		m_playing = false;
		m_playPauseBtn->setCaption(u"boucle");

		m_playing = false;

		Instruction * indexInstruction = App->generatorEngine->getInstruction("PATHS_INDEX");
		std::vector<VectorImage *> images = {new VectorImage(m_savedImage)};

		delete m_workingImage;
		m_workingImage = indexInstruction->execute(images)[0];

		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		delete indexInstruction;
	}

	void AssemblageInterface::applyShapesIndex()
	{
		m_playing = false;
		m_playPauseBtn->setCaption(u"boucle");

		Instruction * indexInstruction = App->generatorEngine->getInstruction("SHAPES_INDEX");
		std::vector<VectorImage *> images = {new VectorImage(m_savedImage)};

		delete m_workingImage;
		m_workingImage = indexInstruction->execute(images)[0];

		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		delete indexInstruction;
	}

	std::string AssemblageInterface::floatToString(const float &val)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << val;
		return stream.str();
	}

	AssemblageInterface::~AssemblageInterface()
	{
		delete m_baseInterface;
		delete m_instructionsInterface;
		delete m_protocol;
		delete m_loopCursor;
		delete m_workingMesh;
		delete m_excerpt;
	}
}
