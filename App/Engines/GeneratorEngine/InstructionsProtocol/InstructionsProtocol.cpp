//
//  InstructionsGroup.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "InstructionsProtocol.hpp"
#include "../InstructionParameters.hpp"

#include "Core/AppObject.hpp"

#include <algorithm>
#include <vector>

InstructionsProtocol::InstructionsProtocol(const std::vector<std::string> &instructionNames):m_name("")
{
	addInstructions(instructionNames);
}

InstructionsProtocol::InstructionsProtocol(const std::vector<std::string> &instructionNames, const std::string &name):m_name(name)
{
	addInstructions(instructionNames);
}

std::vector<VectorImage *> InstructionsProtocol::execute(std::vector<VectorImage *> &vectorImages)
{
	std::vector<VectorImage *> images, transformedImages;

	//Copy input content to preserve integrity
	for(VectorImage * vectorImage : vectorImages)
	{
		images.push_back(new VectorImage(vectorImage));
	}


	//Call each instruction in the group
	for(const std::string &instruction : m_instructionsOrder)
	{
		//Execute instructions
		transformedImages = m_instructions[instruction]->execute(images);

		//Free input images
		for(VectorImage * &inputImage : images)
		{
			delete inputImage;
			inputImage = nullptr;
		}
		
		images.clear();
		images = transformedImages;
	}

	return images;
}

void InstructionsProtocol::addInstruction(const std::string &instructionName)
{
	m_instructionsOrder.push_back(instructionName);

	if(m_instructions.find(instructionName) != m_instructions.end())
		return; //Instruction already stored, do not store again

	m_instructions.insert(std::pair<std::string, InstructionObject *>(instructionName, (InstructionObject *)App->generatorEngine->getInstruction(instructionName)));
}

void InstructionsProtocol::addInstructions(const std::vector<std::string> &instructionNames)
{
	for(const std::string &instructionName : instructionNames)
		addInstruction(instructionName);
}

std::map<std::string, InstructionObject *> InstructionsProtocol::getInstructions() const
{
	return m_instructions;
}

std::vector<std::string> InstructionsProtocol::getInstructionsNames() const
{
	std::vector<std::string> instructions;

	for(std::map<std::string, InstructionObject *>::const_iterator it = m_instructions.begin(); it != m_instructions.end(); ++it)
		instructions.push_back(it->first);

	return instructions;
}

std::vector<std::string> InstructionsProtocol::getInstructionsInOrder() const
{
	return m_instructionsOrder;
}

void InstructionsProtocol::setParameters(InstructionParameters * params)
{
	for(std::map<std::string, InstructionObject *>::const_iterator it = m_instructions.begin(); it != m_instructions.end(); ++it)
		it->second->setParameters(params);
}

void InstructionsProtocol::setParameters(const std::vector<InstructionParameters *> &params)
{
	if(params.size() != m_instructions.size())
		throw new std::runtime_error("Could not set parameters.\nNumber of given parameters must match the number of Instructions in the group.");

	int i = 0;

	for(std::map<std::string, InstructionObject *>::iterator it = m_instructions.begin(); it != m_instructions.end(); ++it, ++i)
	{
		it->second->setParameters(params[i]);
	}
}


void InstructionsProtocol::bindParameter(const uint &instructionID, InstructionParameters * &param)
{
	if(instructionID >= m_instructionsOrder.size())
		throw std::runtime_error("Could not bind parameters. Instruction ID "+std::to_string(instructionID)+" out of range.");

	m_instructionsOrderParameters[instructionID] = param;
}

void InstructionsProtocol::swapInstructions(const uint &first, const uint &second)
{
	if(first > m_instructionsOrder.size() - 1 || second > m_instructionsOrder.size() - 1)
		throw std::runtime_error("Could not swap instructions " + std::to_string(first) + " and " + std::to_string(second) + ".\nInstruction index out of range (" + std::to_string(m_instructionsOrder.size()) + ")");

	std::swap(m_instructionsOrder[first], m_instructionsOrder[second]);
}

void InstructionsProtocol::removeInstruction(const uint &instructionIndex)
{
	if(instructionIndex > m_instructionsOrder.size() - 1)
		throw std::runtime_error("Could not remove instruction " + std::to_string(instructionIndex) + ".\nInstruction index out of range (" + std::to_string(m_instructionsOrder.size()) + ")");

	std::string instructionName = m_instructionsOrder[instructionIndex];

	m_instructionsOrder.erase(m_instructionsOrder.begin() + instructionIndex);

	if(std::find(m_instructionsOrder.begin(), m_instructionsOrder.end(), instructionName) != m_instructionsOrder.end())
		return;

	m_instructionsOrderParameters.erase(instructionIndex);

	delete m_instructions[instructionName];
	m_instructions.erase(instructionName);

}

InstructionsProtocol::~InstructionsProtocol()
{
	for(std::map<std::string, InstructionObject *>::const_iterator it = m_instructions.begin(); it != m_instructions.end(); ++it)
		delete it->second;

	for(std::map<uint, InstructionParameters *>::const_iterator it = m_instructionsOrderParameters.begin(); it != m_instructionsOrderParameters.end(); ++it)
		delete it->second;
}
