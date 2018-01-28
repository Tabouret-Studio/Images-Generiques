//
//  InstructionsGroup.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "InstructionsProtocol.hpp"

#include "Core/AppObject.hpp"

InstructionsProtocol::InstructionsProtocol(const std::vector<std::string> &instructionNames):m_name("")
{
	addInstructions(instructionNames);
}

InstructionsProtocol::InstructionsProtocol(const std::vector<std::string> &instructionNames, const std::string &name):m_name(name)
{
	addInstructions(instructionNames);
}

std::vector<VectorImage *> InstructionsProtocol::execute(const std::vector<VectorImage *> &vectorImages)
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

std::vector<InstructionObject *> InstructionsProtocol::getInstructions() const
{
	std::vector<InstructionObject *> instructions;

	for(std::map<std::string, InstructionObject *>::const_iterator it = m_instructions.begin(); it != m_instructions.end(); ++it)
		instructions.push_back(it->second);

	return instructions;
}

std::vector<std::string> InstructionsProtocol::getInstructionsNames() const
{
	std::vector<std::string> instructions;

	for(std::map<std::string, InstructionObject *>::const_iterator it = m_instructions.begin(); it != m_instructions.end(); ++it)
		instructions.push_back(it->first);

	return instructions;
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

InstructionsProtocol::~InstructionsProtocol()
{
	for(std::map<std::string, InstructionObject *>::const_iterator it = m_instructions.begin(); it != m_instructions.end(); ++it)
		delete it->second;
}
