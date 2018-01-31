//
//  ShapeNoise.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef ShapeNoise_hpp
#define ShapeNoise_hpp

#include "../Instruction.hpp"

/*
Instruction de bruitage des courbes pour une VectorImage
*/
class ShapeNoise: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	ShapeNoise(): Instruction(INSTRUCTION_SOURCE_SHAPES, INSTRUCTION_PROPERTY_GEOMETRY, u"translater aléatoirement") {};
};

#endif /* ShapeNoise_hpp */
