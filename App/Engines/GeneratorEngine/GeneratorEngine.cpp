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
#include <boost/filesystem/fstream.hpp>

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
	//Avoiding const_cast
	std::vector<char> nonConstpath(App->getAppPath().begin(), App->getAppPath().end());
	nonConstpath.push_back('\0');

	//init Python
	Py_SetProgramName(&nonConstpath[0]);

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

	for(boost::filesystem::directory_entry entry : boost::filesystem::directory_iterator(instructionsFolder))
	{
		scriptPath = entry.path();

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
