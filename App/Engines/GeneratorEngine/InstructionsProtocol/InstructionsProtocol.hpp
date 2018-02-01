//
//  InstructionsProtocol.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef InstructionsProtocol_hpp
#define InstructionsProtocol_hpp

//////////////////////
//Forward declarations
class InstructionParameters;

#include "../GeneratorEngine.hpp"
#include "../InstructionObject.hpp"

#include <iostream>

/**
 Holds a list of instructions to be executed in the given order
*/
class InstructionsProtocol: public InstructionObject
{
public:

	//Constructors
	InstructionsProtocol() {};
	InstructionsProtocol(const std::vector<std::string> &instructionNames);
	InstructionsProtocol(const std::vector<std::string> &instructionNames, const std::string &name);

	/**
	 Call the execute function of all the instructions in the protocol

	 @param vectorImages The starting VectorImage
	 @return A new vectorImage with all the instruction applied on
	 */
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

	/**
	 Add a new instruction at the end of the protocol

	 @param instructionName THe instruction to add
	 */
	void addInstruction(const std::string &instructionName);

	/**
	 Add new instructions at the end of the protocol

	 @param instructionNames The instructions to add
	 */
	void addInstructions(const std::vector<std::string> &instructionNames);

	/**
	 Return all the instruction in the protocol

	 @return All the instruction in a vector
	 */
	std::map<std::string, InstructionObject *> getInstructions() const;

	/**
	 Return all the instruction names in the protocol

	 @return All the instruction names in a vector
	 */
	std::vector<std::string> getInstructionsNames() const;

	/**
	 Return the exact instruction order by name

	 @return All the instructions name in order
	 */
	std::vector<std::string> getInstructionsInOrder() const;

	/**
	 Set the given parameter for the instruction.s

	 @param params InstructionParameters object
	 */
	void setParameters(InstructionParameters * params);

	/**
	 Set the given parameters to all the instructions in the protocol
	 The number of given params must match the number of instructions in the group

	 @param params An array of parameters object
	 */
	void setParameters(const std::vector<InstructionParameters *> &params);

	void bindParameter(const uint &instructionID, InstructionParameters * &param);

	InstructionParameters * getParameters(const uint &instructionID) { return m_instructionsOrderParameters[instructionID]; };

	/**
	 Set the protocol name if it has any

	 @param name The name
	 */
	void setName(const std::string &name) { m_name = name; };

	/**
	 Get the protocole name, might be an empty string

	 @return The name
	 */
	inline std::string getName() const { return m_name; };

	/**
	 Swap to instruction in the execution order

	 @param first First instruction
	 @param second Second instruction
	 */
	void swapInstructions(const uint &first, const uint &second);

	void removeInstruction(const uint &instructionIndex);
	
	/**
	 Protocol destructor
	 Delete all instructions in the group
	 */
	virtual ~InstructionsProtocol();

private:

	std::map<std::string, InstructionObject *> m_instructions;
	std::vector<std::string> m_instructionsOrder;
	std::map<uint, InstructionParameters *> m_instructionsOrderParameters;

	std::string m_name;
};

#endif /* InstructionsProtocol_hpp */
