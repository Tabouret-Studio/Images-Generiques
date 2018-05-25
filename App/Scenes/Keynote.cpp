//
//  Keynote.cpp
//  Xcode
//
//  Created by Valentin Dufois on 25/05/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Keynote.hpp"

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

#define LOOP_INTERVAL .2

namespace Scenes
{
	void Keynote::load()
	{
		Scene * scene = new Keynote();
		scene->init();

		App->addScene(scene);
	}

	//////////////
	// This is executed only one time at start up
	///////////
	void Keynote::init()
	{
		//Load renderer
		m_renderer = new SimpleRenderer();
		m_renderer->setBounds(0, 0, 0, 0);
		m_renderer->init();
		App->addScene(m_renderer);

		//prepare loop
		resetLoop();
	}


	//////////////
	// This is executed every frame before render
	///////////
	void Keynote::execute()
	{
		long currTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

		if((m_currentRenderIter + 30 * 1000) < currTime)
			resetLoop();

		protocolLoop();
	}


	//////////////
	// This is executed every frame at render
	///////////
	void Keynote::render()
	{
		//Make sure renderer is active
		m_renderer->enable();
	}

	void Keynote::toggleLoop()
	{
		m_playing = !m_playing;
	}

	InstructionsProtocol * Keynote::getProtocol()
	{
		std::vector<InstructionsProtocol *> protocols = App->generatorEngine->getProtocols();
		std::random_shuffle(protocols.begin(), protocols.end(), Utils::rand);
		return protocols[0];
	}

	void Keynote::resetLoop()
	{
		m_lastIter = std::chrono::steady_clock::now() - std::chrono::duration<int>(100);

		//reset working image
		delete m_workingImage;

		//Dynamic load from index
		m_workingImage = App->indexEngine->getRandomVectorImage();

		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		m_nextInstruction = 0;

		//delete m_protocol;
		m_protocol = getProtocol();

		m_currentRenderIter = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	}

	void Keynote::protocolLoop()
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

		//Send images to renderer
		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		//Increment instruction
		m_nextInstruction++;

		//Reset interval timer
		m_lastIter = std::chrono::steady_clock::now();
	}

	void Keynote::sendToRenderer(VectorImage * vectorImage, const uint &pointSize)
	{
		VectorImage tempImage = *vectorImage;
		tempImage.applyCursor();

		delete m_workingMesh;
		m_workingMesh = tempImage.getMesh();
		m_workingMesh->setPointSize(pointSize);
		m_renderer->addMesh(m_workingMesh);
	}

	void Keynote::applyPathsIndex()
	{
		m_playing = false;

		Instruction * indexInstruction = App->generatorEngine->getInstruction("PATHS_INDEX");
		std::vector<VectorImage *> images = {new VectorImage(m_savedImage)};

		delete m_workingImage;
		m_workingImage = indexInstruction->execute(images)[0];

		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		delete indexInstruction;
	}

	void Keynote::applyShapesIndex()
	{
		m_playing = false;

		Instruction * indexInstruction = App->generatorEngine->getInstruction("SHAPES_INDEX");
		std::vector<VectorImage *> images = {new VectorImage(m_savedImage)};

		delete m_workingImage;
		m_workingImage = indexInstruction->execute(images)[0];

		m_renderer->clear();
		sendToRenderer(m_workingImage, 1);

		delete indexInstruction;
	}

	std::string Keynote::floatToString(const float &val)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << val;
		return stream.str();
	}

	Keynote::~Keynote()
	{
		delete m_protocol;
		delete m_workingMesh;
		delete m_savedImage;
	}
}
