//
//  InstructionObject.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef InstructionObject_h
#define InstructionObject_h

//////////////////////
//Forward declarations

class InstructionParameters;

#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"

#include <vector>

class InstructionObject
{
public:
	/**
	 Execute the instruction

	 @param vectorImages The vector image to use for the instruction
	 @return A new vector image with the instruction applied on
	 */
	virtual std::vector<VectorImage *> execute(std::vector<VectorImage *> vectorImages) = 0;

	/**
	 Set the given parameter for the instruction.s

	 @param params InstructionParameters object
	 */
	virtual void setParameters(InstructionParameters * params) = 0;

	/**
	 Default destructor
	 */
	virtual ~InstructionObject() = default;
};

#endif /* InstructionObject_h */
