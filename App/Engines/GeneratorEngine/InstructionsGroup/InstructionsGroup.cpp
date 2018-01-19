//
//  InstructionsGroup.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "InstructionsGroup.hpp"

#include "Core/AppObject.hpp"

InstructionsGroup::InstructionsGroup(const InstructionName &instructionName)
{
	addInstruction(instructionName);
}

InstructionsGroup::InstructionsGroup(const std::vector<InstructionName> &instructionNames)
{
	addInstructions(instructionNames);
}

VectorImage * InstructionsGroup::execute(VectorImage * vectorImage)
{
	VectorImage * newVector = vectorImage;

	//Call each instruction in the group
	for(InstructionObject * instruction : m_instructions)
		newVector = instruction->execute(newVector);

	return newVector;
}

void InstructionsGroup::addInstruction(const InstructionName &instructionName)
{
	m_instructions.push_back((InstructionObject *)App->generatorEngine->getInstruction(instructionName));
}

void InstructionsGroup::addInstructions(const std::vector<InstructionName> &instructionNames)
{
	for(InstructionName instructionName : instructionNames)
		addInstruction(instructionName);
}
