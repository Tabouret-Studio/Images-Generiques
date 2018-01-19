//
//  InstructionGroup.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef InstructionGroup_hpp
#define InstructionGroup_hpp

//////////////////////
//Forward declarations

#include "../GeneratorEngine.hpp"
#include "../InstructionObject.hpp"

class InstructionsGroup: public InstructionObject
{
public:

	InstructionsGroup() {};
	InstructionsGroup(const InstructionName &instructionName);
	InstructionsGroup(const std::vector<InstructionName> &instructionNames);

	/**
	 Call the execute function of all the instructions in the group

	 @param vectorImage The starting VectorImage
	 @return A new vectorImage with all the instruction applied on
	 */
	VectorImage * execute(VectorImage * vectorImage);

	/**
	 Add a new instruction to the group

	 @param instructionName THe instruction to add
	 */
	void addInstruction(const InstructionName &instructionName);

	/**
	 Add new instructions to the group

	 @param instructionNames The instructions to add
	 */
	void addInstructions(const std::vector<InstructionName> &instructionNames);

	/**
	 Return all the instruction in the group

	 @return All the instruction in a pointer
	 */
	inline std::vector<InstructionObject *> getInstructions() const { return m_instructions; };

private:
	std::vector<InstructionObject *> m_instructions;
};

#endif /* InstructionGroup_hpp */
