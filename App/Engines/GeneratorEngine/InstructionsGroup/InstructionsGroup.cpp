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

std::vector<VectorImage *> InstructionsGroup::execute(std::vector<VectorImage *> vectorImages)
{
	std::vector<VectorImage *> newVector = vectorImages;

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

void InstructionsGroup::setParameters(InstructionParameters * params)
{
	for(InstructionObject * instructionObject : m_instructions)
		instructionObject->setParameters(params);
}

void InstructionsGroup::setParameters(const std::vector<InstructionParameters *> &params)
{
	if(params.size() != m_instructions.size())
		throw new std::runtime_error("Could not set parameters.\nNumber of given parameters must match the number of Instructions in the group.");


}
