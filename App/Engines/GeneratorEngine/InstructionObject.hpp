//
//  InstructionObject.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef InstructionObject_h
#define InstructionObject_h

#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"

class InstructionObject
{
public:
	/**
	 Execute the instruction

	 @param vectorImage The vector image to use for the instruction
	 @return A new vector image with the instruction applied on
	 */
	virtual VectorImage * execute(VectorImage * vectorImage) = 0;
};

#endif /* InstructionObject_h */
