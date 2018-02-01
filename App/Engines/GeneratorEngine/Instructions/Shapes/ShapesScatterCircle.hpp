//
//  ShapesScatterCircle.hpp
//  Xcode
//
//  Created by Valentin Dufois on 01/02/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef ShapesScatterCircle_hpp
#define ShapesScatterCircle_hpp

#include "../Instruction.hpp"

/*
 Instruction de bruitage des courbes pour une VectorImage
 */
class ShapesScatterCircle: public Instruction
{
public:

	static Instruction * get();

	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	ShapesScatterCircle(): Instruction(INSTRUCTION_SOURCE_SHAPES, INSTRUCTION_PROPERTY_SCATTER, u"ceinturer") {};
};

#endif /* ShapesScatterCircle_hpp */
