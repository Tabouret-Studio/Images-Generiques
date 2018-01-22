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

class InstructionsProtocol: public InstructionObject
{
public:

	//Constructors
	InstructionsProtocol() {};
	InstructionsProtocol(const InstructionName &instructionName);
	InstructionsProtocol(const std::vector<InstructionName> &instructionNames);

	/**
	 Call the execute function of all the instructions in the protocol

	 @param vectorImages The starting VectorImage
	 @return A new vectorImage with all the instruction applied on
	 */
	std::vector<VectorImage *> execute(std::vector<VectorImage *> vectorImages);

	/**
	 Add a new instruction at the end of the protocol

	 @param instructionName THe instruction to add
	 */
	void addInstruction(const InstructionName &instructionName);

	/**
	 Add new instructions at the end of the protocol

	 @param instructionNames The instructions to add
	 */
	void addInstructions(const std::vector<InstructionName> &instructionNames);

	/**
	 Return all the instruction in the protocol

	 @return All the instruction in a pointer
	 */
	inline std::vector<InstructionObject *> getInstructions() const { return m_instructions; };

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

	/**
	 Protocol destructor
	 Delete all instructions in the group
	 */
	virtual ~InstructionsProtocol();

private:
	std::vector<InstructionObject *> m_instructions;
};

#endif /* InstructionsProtocol_hpp */
