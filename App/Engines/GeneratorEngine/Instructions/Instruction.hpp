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

/**
 An Instruction uses one or more VectorImage.
 It returns a new one based on modifications made with the given ones.
 Each instruction is independant and can be used in combination with any other.
 */
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

	/**
	 Default destructor
	 Erase the parameters
	 */
	virtual ~Instruction()
	{
		if(m_parameters != nullptr)
			delete m_parameters;
	};

protected:
	Instruction(): m_parameters(nullptr) {};

	InstructionParameters * m_parameters;
};

#include "PythonInstruction.hpp"

//Paths
#include "Paths/PathsOrderRandomizer.hpp"
#include "Paths/PathsChaining.hpp"
#include "Beziers/BeziersLinearAlizer.hpp"


#endif /* Instruction_h */
