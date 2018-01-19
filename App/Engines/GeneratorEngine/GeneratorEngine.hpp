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

#include <functional>
#include <map>

/**
 Instruction enumerations
 */
enum InstructionName
{
	INSTRUCTION_PATHS_ORDER_RANDOMIZER,
	INSTRUCTION_PATHS_CHAINING
};

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
	Instruction * getInstruction(const InstructionName &instruction);

private:

	//Singleton
	GeneratorEngine();
	static bool m_instanciated;

	//Map with all the instructions and instructions getters
	std::map<InstructionName, std::function<Instruction *(void)>> m_instructionsIndex;
	void registerInstructions();
};

#endif /* GeneratorEngine_hpp */
