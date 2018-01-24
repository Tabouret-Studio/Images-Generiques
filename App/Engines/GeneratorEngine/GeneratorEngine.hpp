//
//  GeneratorEngine.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef GeneratorEngine_hpp
#define GeneratorEngine_hpp

//////////////////////
//Forward declarations
class Instruction;

#include <Python.h>
#include <functional>
#include <map>

/**
 The Generator Engine holds methods and classes to manipulate and generate vector images. It goals is to allow for unified, simplified access to VectorImage manipulations (Instructions)
 */
class GeneratorEngine
{
public:

	/**
	 Instanciate the generator as a Singleton
	 */
	static void instanciate();

	/**
	 Instanciate and return the asked instruction

	 @param instruction The instructionName to return
	 @return An instanciated Instruction
	 */
	Instruction * getInstruction(const std::string &instruction);

private:

	//Singleton
	GeneratorEngine();
	static bool m_instanciated;

	//Maps with all the instructions and instructions getters
	std::map<std::string, std::function<Instruction *(void)>> m_instructionsIndex;
	std::map<std::string, instructionFormat> m_instructionsFormats;

	/**
	 Register all CPP instructions
	 */
	void registerCPPInstructions();

	/**
	 Register all python instructions (assets/instructions/ *.py)
	 */
	void registerPythonInstructions();

	/**
	 Register an instruction in the engine

	 @param format Instruction format
	 @param instructionName Name of the instruction
	 @param loader Function to load the instruction
	 */
	void registerInstruction(const instructionFormat &format, const std::string &instructionName, std::function<Instruction *(void)> loader);

	Instruction * getPythonInstruction(const std::string &scriptName);
};

#endif /* GeneratorEngine_hpp */
