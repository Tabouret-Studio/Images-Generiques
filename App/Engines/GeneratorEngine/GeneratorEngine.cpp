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

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <iostream>
#include <iterator>
#include <vector>

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
	char *cstr = new char[App->getAppPath().length() + 1];
	strcpy(cstr, App->getAppPath().c_str());

	//init Python
	Py_SetProgramName(cstr);

	//The cstr is keeped because Py needs it later --'
	//delete cstr;

	registerCPPInstructions();
	registerPythonInstructions();
}



Instruction * GeneratorEngine::getInstruction(const std::string &instruction)
{
	if(m_instructionsIndex.find(instruction) == m_instructionsIndex.end())
		throw std::runtime_error("Could not run instruction "+instruction+".\nThe instruction "+instruction+" could not be found.");

	if(m_instructionsFormats[instruction] == INSTRUCTION_CPP)
		return m_instructionsIndex[instruction]();

	return getPythonInstruction(instruction);
}




void GeneratorEngine::registerCPPInstructions()
{
	//Register all instructions

	//Paths
	registerInstruction(INSTRUCTION_CPP, "PATHS_ORDER_RANDOMIZER", PathsOrderRandomizer::get);
	registerInstruction(INSTRUCTION_CPP, "PATHS_CHAINING", PathsChaining::get);
}

void GeneratorEngine::registerPythonInstructions()
{
	boost::filesystem::path instructionsFolder = App->getAppPath() + "assets/instructions/";

	boost::filesystem::path scriptPath;
	std::string scriptName;

	if(!boost::filesystem::exists(instructionsFolder))
		return; //No folder, nothing to iterate

	std::vector<boost::filesystem::directory_entry> entries;
	std::copy(boost::filesystem::directory_iterator(instructionsFolder), boost::filesystem::directory_iterator(), std::back_inserter(entries));

	for(std::vector<boost::filesystem::directory_entry>::const_iterator entry = entries.begin(); entry != entries.end(); ++entry)
	{
		scriptPath = (*entry).path();

		if(boost::filesystem::is_directory(scriptPath))
		   continue; //Ignore sub-directories (for now ?)

		if(scriptPath.filename_is_dot() || scriptPath.filename_is_dot_dot() || scriptPath.empty())
			continue; //Ignore useless entries

		if(scriptPath.extension() != ".py")
			continue; //Ignore non python script

		scriptName = scriptPath.filename().generic_string();
		scriptName = scriptName.substr(0, scriptName.length() - 3);

		registerInstruction(INSTRUCTION_PYTHON, scriptName, nullptr);
	}
}

void GeneratorEngine::registerInstruction(const instructionFormat &format, const std::string &instructionName, std::function<Instruction *(void)> loader)
{
	m_instructionsIndex.insert(std::pair<std::string, std::function<Instruction *(void)>>(instructionName, loader));
	m_instructionsFormats.insert(std::pair<std::string, instructionFormat>(instructionName, format));
}

Instruction * GeneratorEngine::getPythonInstruction(const std::string &scriptName)
{
	return PythonInstruction::get(scriptName);
}
