//
//  InstructionsGroup.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "InstructionsProtocol.hpp"

#include "Core/AppObject.hpp"

InstructionsProtocol::InstructionsProtocol(const InstructionName &instructionName)
{
	addInstruction(instructionName);
}

InstructionsProtocol::InstructionsProtocol(const std::vector<InstructionName> &instructionNames)
{
	addInstructions(instructionNames);
}

std::vector<VectorImage *> InstructionsProtocol::execute(std::vector<VectorImage *> vectorImages)
{
	std::vector<VectorImage *> newVector = vectorImages;

	//Call each instruction in the group
	for(InstructionObject * instruction : m_instructions)
		newVector = instruction->execute(newVector);

	return newVector;
}

void InstructionsProtocol::addInstruction(const InstructionName &instructionName)
{
	m_instructions.push_back((InstructionObject *)App->generatorEngine->getInstruction(instructionName));
}

void InstructionsProtocol::addInstructions(const std::vector<InstructionName> &instructionNames)
{
	for(InstructionName instructionName : instructionNames)
		addInstruction(instructionName);
}

void InstructionsProtocol::setParameters(InstructionParameters * params)
{
	for(InstructionObject * instructionObject : m_instructions)
		instructionObject->setParameters(params);
}

void InstructionsProtocol::setParameters(const std::vector<InstructionParameters *> &params)
{
	if(params.size() != m_instructions.size())
		throw new std::runtime_error("Could not set parameters.\nNumber of given parameters must match the number of Instructions in the group.");

	int i = 0;

	for(std::vector<InstructionObject *>::iterator it = m_instructions.begin(); it != m_instructions.end(); ++it, ++i)
	{
		(*it)->setParameters(params[i]);
	}
}

InstructionsProtocol::~InstructionsProtocol()
{
	for(std::vector<InstructionObject *>::iterator it = m_instructions.begin(); it != m_instructions.end(); ++it)
	{
		delete *it;
	}
}
