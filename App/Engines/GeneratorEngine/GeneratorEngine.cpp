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
#include "InstructionsProtocol/InstructionsProtocol.hpp"
#include "InstructionObject.hpp"

#ifdef __WIN32__

#else
	#include <dirent.h>
#endif

#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>

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
	//Ugly conversion because Py_SetProgramName is not marked as const despite not modifying the var (thx c89)
	std::string pathToInstruction = App->getAppPath() + "assets/instructions/";
	char *cstr = new char[pathToInstruction.length() + 1];
	strcpy(cstr, pathToInstruction.c_str());

	//init Python
	Py_SetProgramName(cstr);

	//Register instructions
	registerCPPInstructions();
	registerPythonInstructions();
}

Instruction * GeneratorEngine::getInstruction(const std::string &instruction) const
{
	if(!instructionExist(instruction))
		throw std::runtime_error("Could not run instruction "+instruction+".\nThe instruction "+instruction+" could not be found.");

	if(m_instructionsFormats.at(instruction) == INSTRUCTION_CPP)
		return m_instructionsIndex.at(instruction)();

	return getPythonInstruction(instruction);
}

std::map<std::string, Instruction *> GeneratorEngine::getAllInstructions() const
{
	std::map<std::string, Instruction *> instructions;

	for(std::map<std::string, std::function<Instruction *(void)>>::const_iterator it = m_instructionsIndex.begin(); it != m_instructionsIndex.end(); ++it)
		instructions.insert(std::pair<std::string, Instruction *>(it->first, getInstruction(it->first)));

	return instructions;
}

std::vector<std::string> GeneratorEngine::getAllInstructionNames() const
{
	std::vector<std::string> instructions;

	for(std::map<std::string, std::function<Instruction *(void)>>::const_iterator it = m_instructionsIndex.begin(); it != m_instructionsIndex.end(); ++it)
		instructions.push_back(it->first);

	return instructions;
}

bool GeneratorEngine::instructionExist(const std::string &instruction) const
{
	if(m_instructionsIndex.find(instruction) == m_instructionsIndex.end())
		return false;

	return true;
}

std::vector<InstructionsProtocol *> GeneratorEngine::getProtocols() const
{
	std::vector<InstructionsProtocol *> protocols;

	for(std::map<std::string, InstructionsProtocol *>::const_iterator it = m_protocols.begin(); it != m_protocols.end(); ++it)
		protocols.push_back(it->second);

	return protocols;
}

InstructionsProtocol * GeneratorEngine::getProtocol(const std::string &protocolName) const
{
	if(m_protocols.find(protocolName) == m_protocols.end())
		throw std::runtime_error("The protocol " + protocolName + "is not a valid protocol name.");

	return m_protocols.at(protocolName);
}

void GeneratorEngine::registerCPPInstructions()
{
	//Register all instructions

	//Paths
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_AMPLITUDE", BeziersAmplitude::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_OPPOSING1", BeziersHandlesReversing::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_OPPOSING2", BeziersOpposing::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_ORDER_CHAINING", PathsChaining::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_INDEX", PathsIndex::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_INVERT", PathsInvert::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_LINEARALIZER", PathsLinearAlizer::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_NOISETRANSLATE", PathsNoise::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_ORDER_INVERT", PathsOrderInvert::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_ORDER_RANDOMIZER", PathsOrderRandomizer::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_ORIENTRANDOMIZER", PathsOrientRandomizer::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_GEOMETRY_SQUARIFY", PathsSquarify::get);

	//Shapes
	registerInstruction(INSTRUCTION_CPP, "SHAPES_INDEX", ShapeIndex::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_GEOMETRY_NOISETRANSLATE", ShapeNoise::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_CHAINING", ShapesChaining::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_GEOMETRY_NOISEROTATE", ShapesGeometryRandomizer::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_ORDER_INVERT", ShapesOrderInvert::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_ORDER_RANDOMIZER", ShapesOrderRandomizer::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_SYMX", ShapeSymX::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_SYMY", ShapeSymY::get);
	registerInstruction(INSTRUCTION_CPP, "SHAPES_SCATTER_CIRCLE", ShapesScatterCircle::get);
}


void GeneratorEngine::registerPythonInstructions()
{
#ifndef IG_PYTHON_INSTRUCTIONS
	return;
#elif
#	ifdef __WIN32__

		std::cout << "Directory parsing has not been implemented yet for windows.\nPython instructions will not be available." << std::endl;

#	else

		DIR *dir;
		struct dirent *ent;

		std::string path = App->getAppPath() + "assets/instructions/";

		if((dir = opendir(path.c_str())) == NULL)
		{
			std::cout << "Python instructions folder could not be parsed.\nPython instructions will not be available" << std::endl;
			return;
		}

		while((ent = readdir(dir)) != NULL)
		{
			std::string scriptName = ent->d_name;

			if(scriptName.size() < 4)
				continue;

			if(scriptName.substr(scriptName.length() - 3, std::string::npos) != ".py")
				continue; //Ignore non python script

			scriptName = scriptName.substr(0, scriptName.length() - 3);

			registerInstruction(INSTRUCTION_PYTHON, scriptName, nullptr);
		}

		closedir(dir);

	#endif
#endif
}


void GeneratorEngine::registerInstruction(const instructionFormat &format, const std::string &instructionName, std::function<Instruction *(void)> loader)
{
	m_instructionsIndex.insert(std::pair<std::string, std::function<Instruction *(void)>>(instructionName, loader));
	m_instructionsFormats.insert(std::pair<std::string, instructionFormat>(instructionName, format));
}

Instruction * GeneratorEngine::getPythonInstruction(const std::string &scriptName) const
{
#ifndef IG_PYTHON_INSTRUCTIONS
	throw std::runtime_error("Python instructions have been deactivated.");
#elif
	return PythonInstruction::get(scriptName);
#endif
}

void GeneratorEngine::registerProtocols()
{
#ifdef __WIN32__

	std::cout << "Directory parsing has not been implemented yet for windows.\nPredefined protocols will not be available." << std::endl;

#else

	DIR *dir;
	struct dirent *ent;

	std::string path = App->getAppPath() + "assets/protocols/";

	if((dir = opendir(path.c_str())) == NULL)
	{
		std::cout << "Protocols folder could not be parsed.\nPredefined protocols will not be available" << std::endl;
		return;
	}

	while((ent = readdir(dir)) != NULL)
	{
		std::string protocoleFile = ent->d_name;

		if(protocoleFile.size() < 6)
			continue;

		if(protocoleFile.substr(protocoleFile.length() - 5, std::string::npos) != ".json")
			continue; //Ignore non jsons script

		protocoleFile = protocoleFile.substr(0, protocoleFile.length() - 5);

		registerProtocol(protocoleFile);
	}

	closedir(dir);

#endif
}


void GeneratorEngine::registerProtocol(const std::string &filename)
{
	//Open file
	std::ifstream file(App->getAppPath() + "assets/protocols/" + filename + ".json");

	if(!file)
		return;

	std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	nlohmann::json protocolJSON = nlohmann::json::parse(content);

	InstructionsProtocol * protocol = new InstructionsProtocol();
	protocol->setName(filename);

	for(const std::string &instructionName : protocolJSON)
	{
		if(!instructionExist(instructionName))
		{
			delete protocol;
			std::cout << "Protocol " + filename + " has not been registered because the instruction " + instructionName + " could not be found." << std::endl;
			return;
		}

		protocol->addInstruction(instructionName);
	}

	m_protocols.insert(std::pair<std::string, InstructionsProtocol *>(filename, protocol));
}
