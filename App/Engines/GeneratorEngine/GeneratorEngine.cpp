//
//  GeneratorEngine.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "GeneratorEngine.hpp"

#include "Core/AppObject.hpp"
#include "Instructions/Instruction.hpp"
#include "InstructionObject.hpp"

bool GeneratorEngine::m_instanciated = false;

/**
 * Instanciate the engine as a Singleton
 */
void GeneratorEngine::instanciate()
{
	if(m_instanciated)
		return;

	App->generatorEngine = new GeneratorEngine();

	m_instanciated = true;
}

GeneratorEngine::GeneratorEngine()
{
	registerInstructions();
}

Instruction * GeneratorEngine::getInstruction(const InstructionName &instruction)
{
	return m_instructionsIndex[instruction]();
}

void GeneratorEngine::registerInstructions()
{
	//Register all instructions

	//Paths
	m_instructionsIndex.insert(std::pair<InstructionName, std::function<Instruction *(void)>>
							   (INSTRUCTION_PATHS_ORDER_RANDOMIZER, PathsOrderRandomizer::get));
	m_instructionsIndex.insert(std::pair<InstructionName, std::function<Instruction *(void)>>
							   (INSTRUCTION_PATHS_CHAINING, PathsChaining::get));
	m_instructionsIndex.insert(std::pair<InstructionName, std::function<Instruction *(void)>>
							   (INSTRUCTION_PATHS_CHAINING, PathsChaining::get));
}
