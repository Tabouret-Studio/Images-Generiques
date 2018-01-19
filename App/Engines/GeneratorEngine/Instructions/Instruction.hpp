//
//  Instruction.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef Instruction_h
#define Instruction_h

#include "../InstructionObject.hpp"
#include "../InstructionParameters.hpp"

class Instruction: public InstructionObject
{
public:
	/**
	 Return the instruction properly instaciated

	 @return The instruction
	 */
	static Instruction * get();

	/**
	 Execute the instruction with the given VectorImage

	 @param vectorImages The VectorImage to use
	 @return A new, transformed VectorImage
	 */
	virtual std::vector<VectorImage *> execute(std::vector<VectorImage *> vectorImages) = 0;

	/**
	 Set the parameters to use when executing

	 @param parameters An InstructionParameters object
	 */
	inline void setParameters(InstructionParameters * parameters) { m_parameters = parameters; };

	/**
	 Return the parameters object used by the instruction

	 @return An InstructionParameters object
	 */
	inline InstructionParameters *  getParameters() { return m_parameters; };

protected:
	Instruction() {};

	InstructionParameters * m_parameters = nullptr;
};

/////////////////////////////////
//All the instructions comes here

//Paths
#include "Paths/PathsOrderRandomizer.hpp"
#include "Paths/PathsChaining.hpp"

//
/////////////////////////////////

#endif /* Instruction_h */
